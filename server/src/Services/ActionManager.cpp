#include "../../include/Services/ActionManager.h"

ActionManager::ActionManager(GameData& gameData) :
    gameData(gameData),
    streetActionData(),
    numPlayersInStreet({0, false})
{
    setActiveActionAsNone();
}

void ActionManager::clearStreetActionData() {
    streetActionData.numCalls = 0;
    streetActionData.numChecks = 0;
    streetActionData.numFolded = 0;
    streetActionData.numAllInBet = 0;
    streetActionData.numAllInCall = 0;
    streetActionData.limpedPreflop = true;
}

int ActionManager::findNumSittingOut() {
    if (streetActionData.numAllInBet > 0) {
        return streetActionData.numAllInBet + streetActionData.numAllInCall;
    } 
    return streetActionData.numAllInCall;
}

void ActionManager::setActiveActionAsNone() {
    shared_ptr<Action> noActiveAction = make_shared<NoneAction>();
    gameData.setActiveAction(noActiveAction);
}

void ActionManager::setNumInitialPlayers() {
    auto& [num, isSet] = numPlayersInStreet;
    if (isSet) return;
    numPlayersInStreet = {GameUtil::getNumPlayersInHand(gameData), true};
}

void ActionManager::resetInitialPlayers() {
    numPlayersInStreet = {0, false};
}

void ActionManager::updateStreetActionData(ActionType actionType) {
    switch (actionType) {
        case ActionType::BET:
        case ActionType::RAISE:
            streetActionData.numCalls = 0;
            streetActionData.numSittingOut = findNumSittingOut();
            streetActionData.limpedPreflop = false;
            break;
        case ActionType::ALL_IN_BET:
        case ActionType::ALL_IN_RAISE:
            streetActionData.numCalls = 0;
            streetActionData.numSittingOut = findNumSittingOut();
            streetActionData.numAllInBet += 1;
            streetActionData.limpedPreflop = false;
            break;
        case ActionType::POST_SMALL:
        case ActionType::POST_BIG:
            streetActionData.numCalls = 0;
            break;
        case ActionType::CALL: 
            streetActionData.numCalls += 1;
            break;
        case ActionType::ALL_IN_CALL:
            streetActionData.numAllInCall += 1;
            streetActionData.numSittingOut += 1;
            break;
        case ActionType::FOLD:
            streetActionData.numFolded += 1;
            break;
        case ActionType::CHECK:
            streetActionData.numChecks += 1;
            streetActionData.limpedPreflop = false;
            break;
        default:
            break;
    }
}

void ActionManager::handleBlinds() {
    auto smallB = gameData.getSmallBlind();
    auto bigB = gameData.getBigBlind();
    auto smallId = gameData.getSmallBlindPlayer()->getId();
    auto bigId = gameData.getBigBlindPlayer()->getId();

    addNewAction(smallId, ActionType::POST_SMALL, smallB);
    addNewAction(bigId, ActionType::POST_BIG, bigB);
}

void ActionManager::addNewAction(string idOrName, ActionType actionType, size_t amount) {
    // Update StreetActionData (internal tracking of action types in a given street)
    updateStreetActionData(actionType);

    // Create the new action shared pointer
    shared_ptr<Action> newAction;
    switch(actionType) {
        case ActionType::ALL_IN_BET:newAction = make_shared<AllInBetAction>(idOrName, amount); break;
        case ActionType::ALL_IN_CALL: newAction = make_shared<AllInCallAction>(idOrName, amount); break;
        case ActionType::ALL_IN_RAISE: newAction = make_shared<AllInRaiseAction>(idOrName, amount); break;
        case ActionType::BET: newAction = make_shared<BetAction>(idOrName, amount); break;
        case ActionType::CALL: newAction = make_shared<CallAction>(idOrName, amount); break;
        case ActionType::CHECK: newAction = make_shared<CheckAction>(idOrName); break;
        case ActionType::FOLD: newAction = make_shared<FoldAction>(idOrName); break;
        case ActionType::RAISE: newAction = make_shared<RaiseAction>(idOrName, amount); break;
        case ActionType::POST_SMALL: newAction = make_shared<PostSmallAction>(idOrName, amount); break;
        case ActionType::POST_BIG: newAction = make_shared<PostBigAction>(idOrName, amount); break;
        default: newAction = make_shared<NoneAction>(); break;
    }

    // NOW, UPDATE THE GAME DATA:

    // Player-specific attributes:
   auto player = GameUtil::getPlayer(gameData, idOrName);
   if (newAction->getAmount() != 0) player->reduceChips(newAction->getAmount() - player->getRecentBet());
   player->setPlayerStatus(ActionUtil::inferStatusFromActionType(actionType));

   // If recent bet > 0, but most recent action is check, this means the BB
   // has checked their option. Do not set recent bet to 0 (check).
   // In this case, don't 
   if (actionType == ActionType::CHECK && player->getRecentBet() > 0) player->setRecentBet(player->getRecentBet());
   else if (actionType != ActionType::FOLD) player->setRecentBet(amount);

    // Shared information in the Game Data
    gameData.addActionToTimeline(newAction);
    if (ActionUtil::isActionAggressive(actionType)) gameData.setActiveAction(newAction);
    if (gameData.getActiveAction() == nullptr) gameData.setActiveAction(make_shared<NoneAction>());
}

void ActionManager::generatePossibleActionsForCurPlayer() {
    string curPlayerId = gameData.getCurPlayer()->getId();
    bool isBigBlind = GameUtil::isPlayerBigBlind(gameData, curPlayerId);

    size_t playerStack = gameData.getCurPlayer()->getInitialChips();
    size_t otherBig = GameUtil::getBigStackAmongOthers(gameData);
    size_t activeBet = GameUtil::getActiveActionAmount(gameData);
    size_t stdRaise = 2 * activeBet;

    // maxBetAmount = min(player's stack, biggest stack among other players)
    size_t maxBetAmount = ActionUtil::getMaxBetAmount(gameData);

    // Create ALL possible actions:
    auto newBet = make_shared<PossibleBet>(maxBetAmount);
    auto newAllInBet = make_shared<PossibleAllInBet>(playerStack);
    auto newStdRaise = make_shared<PossibleRaise>(stdRaise, maxBetAmount);
    auto newRaiseToNextBigStack = make_shared<PossibleRaise>(otherBig, 0);
    auto newAllInRaise = make_shared<PossibleAllInRaise>(playerStack);
    auto newCall = make_shared<PossibleCall>(activeBet);
    auto newAllInCall = make_shared<PossibleAllInCall>(playerStack);
    auto newCheck = make_shared<PossibleCheck>();
    auto newFold = make_shared<PossibleFold>();

    // Then, add possible actions that are valid given the betting action:
    vector<shared_ptr<PossibleAction>> possibleActions;

    // Edge case where all players limp and the BB has the option to 'check'
    bool preflopLimp = false;

    // Get the most recent action in the street that is not a CALL or FOLD
    ActionType recentActionType = GameUtil::getActiveActionType(gameData);
    switch(recentActionType) {
        case ActionType::POST_BIG:
            if (isBigBlind) preflopLimp = true;
        case ActionType::BET:
        case ActionType::RAISE:
        case ActionType::ALL_IN_BET:
        case ActionType::ALL_IN_RAISE:
        case ActionType::POST_SMALL:
            // CALL
            if (preflopLimp) possibleActions.push_back(newCheck);
            else if (playerStack > activeBet) possibleActions.push_back(newCall);
            else possibleActions.push_back(newAllInCall);

            // RAISE
            if (playerStack > activeBet) {
                if (playerStack > otherBig) {
                    if (stdRaise >= otherBig) {
                        possibleActions.push_back(newRaiseToNextBigStack);
                    }
                    else if (stdRaise < otherBig) {
                        possibleActions.push_back(newStdRaise);
                    }
                } else if (otherBig >= playerStack) {
                    if (stdRaise >= playerStack) {
                        possibleActions.push_back(newAllInRaise);
                    }
                    else if (stdRaise < playerStack) {
                        possibleActions.push_back(newStdRaise);
                        possibleActions.push_back(newAllInRaise);
                    }
                }
            }

            // FOLD
            possibleActions.push_back(newFold);
            break;
        default: 
            // CHECK, BET, FOLD
            possibleActions.push_back(newCheck);
            possibleActions.push_back(newBet);
            if (otherBig >= playerStack) possibleActions.push_back(newAllInBet);
            possibleActions.push_back(newFold);
            break;
    }

    // Update the list of possible actions for the current player in Game Data
    gameData.setPossibleActions(possibleActions);
}

bool ActionManager::isActionsFinished() {
    // Find the number of players that *began* the current street
    setNumInitialPlayers();

    int initialPlayers = numPlayersInStreet.first;
    bool isActionsFinished = false;
    int checks = streetActionData.numChecks;
    int calls = streetActionData.numCalls;
    int folded = streetActionData.numFolded;
    int sittingOut = streetActionData.numSittingOut;

    // Conditions for the completion of actions

    // Case 1: Preflop and players limp. BB checks (calls) to signify no further raises.
    // Note: The BB check functions as a 'call' to the active bet.
    if ((streetActionData.limpedPreflop == true) &&
        (checks == 1) &&
        (calls == (initialPlayers - folded - 1))) isActionsFinished = true;

    // Case 2: All players have checked through.
    else if ((streetActionData.limpedPreflop == false) &&
        checks == initialPlayers - folded) isActionsFinished = true;

    // Case 3: A player bets/raises and remaining players call or fold
    // Note: The "-1" at the end represents the initial aggressor who bet/raised
    else if ((streetActionData.limpedPreflop == false) &&
            (calls == (initialPlayers - folded - sittingOut - 1))) isActionsFinished = true;
    
    // Case 4: All but one player has folded in the hand
    else if (folded == initialPlayers - 1) isActionsFinished = true;

    // If actions are finished, update the StreetActionData, numPlayersInStreet (internal) and GameData (shared)
    if (isActionsFinished) {
        clearStreetActionData();
        resetInitialPlayers();

        // Player Attributes
        GameUtil::setPlayerInitialToCurChips(gameData);
        // GameUtil::resetPlayerRecentBets(gameData);

        // Game Data Attributes
        gameData.clearActionTimeline();
        setActiveActionAsNone();

        // Return true so the game controller knows to transition to the next street!
        return true;
    }
    return false;
}

bool ActionManager::isShortPlayersInHand() {
    if (GameUtil::isShortPlayersInHand(gameData)) {
        cout << "(+) Action Manager: Less than 2 players left in the hand. Skipping betting streets.\n" << endl;
        return true;
    }
    return false;
}