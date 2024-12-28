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
   player->reduceChips(newAction->getAmount() - player->getRecentBet());
   player->setPlayerStatus(ActionUtil::inferStatusFromActionType(actionType));
   if (actionType != ActionType::FOLD) player->setRecentBet(amount);

    // Shared information in the Game Data
    gameData.addActionToTimeline(newAction);
    if (ActionUtil::isActionAggressive(actionType)) gameData.setActiveAction(newAction);
    if (gameData.getActiveAction() == nullptr) gameData.setActiveAction(make_shared<NoneAction>());
}

void ActionManager::generatePossibleActionsForCurPlayer() {
    string curPlayerId = gameData.getCurPlayerId();
    
    bool isBigBlind = GameUtil::isPlayerBigBlind(gameData, curPlayerId);
    bool canRaise = ActionUtil::canPlayerRaise(gameData, curPlayerId);
    bool canMinRaise = ActionUtil::canPlayerMinRaise(gameData, curPlayerId);
    bool canBetAllIn = ActionUtil::canPlayerAllInBet(gameData, curPlayerId);
    bool canCallActiveBet = ActionUtil::canPlayerCallActiveBet(gameData, curPlayerId);

    size_t curPlayerStack = GameUtil::getPlayerInitialChips(gameData, curPlayerId);
    size_t minRaiseAmount = ActionUtil::getMinRaiseAmount(gameData, curPlayerId);
    size_t maxBetAmount = ActionUtil::getMaxBetAmount(gameData, curPlayerId);
    size_t callAmount = ActionUtil::getCallAmount(gameData, curPlayerId);

    // POSSIBLE BET
    // Min: 0 and Max: minimum of (player's stack, biggest stack among others)
    auto newBet = make_shared<PossibleBet>(maxBetAmount);

    // If player's stack < biggest stack among others, option for all-in bet
    auto newAllInBet = make_shared<PossibleAllInBet>(maxBetAmount);

    // POSSIBLE RAISE
    // Min: minimum of (player's stack, min raise)
    // Max: minimum of (player's stack, biggest stack among others)
    auto newRaise = make_shared<PossibleRaise>(minRaiseAmount, maxBetAmount);

    // If active bet < player stack < min raise
    auto newAllInRaise = make_shared<PossibleAllInRaise>(minRaiseAmount);

    // POSSIBLE CALL
    // Amount is the minimum of (active bet to match, player's stack)
    auto newCall = make_shared<PossibleCall>(callAmount);

    // If player's stack < active bet to match, then all-in to call
    auto newAllInCall = make_shared<PossibleAllInCall>(callAmount);

    // POSSIBLE CHECK OF FOLD (No amounts)
    auto newCheck = make_shared<PossibleCheck>();
    auto newFold = make_shared<PossibleFold>();

    // ASSEMBLE THE VECTOR OF POSSIBLE ACTIONS

    vector<shared_ptr<PossibleAction>> possibleActions;

    // Get the most active action that is not a CALL or FOLD
    ActionType activeActionType = GameUtil::getActiveActionType(gameData);
    switch(activeActionType) {
        case ActionType::POST_BIG:
        // Edge Case: Preflop, players have limped around to the BB.
            // The BB option should be check (instead of call), raise or fold
            if (isBigBlind) {
                possibleActions.push_back(newCheck);
            } else {
                if (canCallActiveBet) possibleActions.push_back(newCall);
                if (!canCallActiveBet) possibleActions.push_back(newAllInCall);
            }
            if (canRaise && canMinRaise) possibleActions.push_back(newRaise);
            if (canRaise && !canMinRaise) possibleActions.push_back(newAllInRaise);
            possibleActions.push_back(newFold);
            break;
        case ActionType::BET:
        case ActionType::RAISE:
        case ActionType::ALL_IN_BET:
        case ActionType::ALL_IN_RAISE:
        case ActionType::POST_SMALL:
            if (canCallActiveBet) possibleActions.push_back(newCall);
            if (!canCallActiveBet) possibleActions.push_back(newAllInCall);
            if (canRaise && canMinRaise) possibleActions.push_back(newRaise);
            if (canRaise && !canMinRaise) possibleActions.push_back(newAllInRaise);
            possibleActions.push_back(newFold);
            break;
        default: 
            possibleActions.push_back(newCheck);
            possibleActions.push_back(newBet);
            if (canBetAllIn) possibleActions.push_back(newAllInBet);
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