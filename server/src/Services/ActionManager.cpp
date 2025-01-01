#include "../../include/Services/ActionManager.h"
#include "../../include/Entities/Actions/NoneAction.h"

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

void ActionManager::addNewAction(string idOrName, ActionType actionType, uint32_t amount) {
    // Update the internal tracking of action types in a betting street
    updateStreetActionData(actionType);

    // Create a shared pointer to the new action instance
    shared_ptr<Action> newAction = ActionUtil::createAction(idOrName, actionType, amount);

    // Update player's attributes in Game Data
    updateAttributesAfterAction(idOrName, newAction);

    // Update timeline and active action in Game Data
    updateGameDataAfterAction(newAction);
}

void ActionManager::generatePossibleActionsForCurPlayer() {
    // Fetch data related for the player to act
    string curPlayerId = gameData.getCurPlayer()->getId();
    bool isBigBlind = GameUtil::isPlayerBigBlind(gameData, curPlayerId);
    uint32_t playerStack = gameData.getCurPlayer()->getInitialChips();
    uint32_t otherBig = GameUtil::getBigStackAmongOthers(gameData);
    uint32_t activeBet = GameUtil::getActiveActionAmount(gameData);
    uint32_t stdRaise = 2 * activeBet;

    // Then, add possible actions that are valid given the betting action:
    vector<shared_ptr<PossibleAction>> possibleActions;
    ActionType recentType = GameUtil::getActiveActionType(gameData);
    addPossibleChecks(possibleActions, recentType, isBigBlind);
    addPossibleBets(possibleActions, recentType, playerStack, otherBig);
    addPossibleCalls(possibleActions, recentType, playerStack, activeBet, isBigBlind);
    addPossibleRaises(possibleActions, recentType, playerStack, otherBig, activeBet);
    addPossibleFolds(possibleActions);

    // Update the list of possible actions for the player to act in Game Data
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

void ActionManager::updateAttributesAfterAction(const string& idOrName, const shared_ptr<Action>& newAction) {
    auto player = GameUtil::getPlayer(gameData, idOrName);
    uint32_t amount = newAction->getAmount();
    ActionType type = newAction->getActionType();

    // Update player's chips
    // Only reduce chips if the new action has an amount > 0
    // Important because a BB can have a recent bet > 0, but check their option
    // In this case, we don't want need to reduce any chips
    if (amount != 0) {
        player->reduceChips(newAction->getAmount() - player->getRecentBet());
    }

    // Update player's status
    player->setPlayerStatus(ActionUtil::inferStatusFromActionType(type));

    // Update player's recent bet
    // If recent bet > 0 but new action is check, this is an edge case
    // where BB has checked their option
    // In this case, we do not set recent bet to 0 since they have already
    // posted a blind (which counts as a 'bet')
    if (type == ActionType::CHECK && player->getRecentBet() > 0) player->setRecentBet(player->getRecentBet());
    else if (type != ActionType::FOLD) player->setRecentBet(amount);
}

void ActionManager::updateGameDataAfterAction(const shared_ptr<Action>& newAction) {
    ActionType type = newAction->getActionType();

    // Add action to the timeline
    gameData.addActionToTimeline(newAction);

    // Set the action as active if aggressive
    // An aggressive action must be responded to e.g. players must call a bet or fold
    // Vice versa, a check would be non-aggressive as players do not need to respond
    if (ActionUtil::isActionAggressive(type)) gameData.setActiveAction(newAction);
    if (gameData.getActiveAction() == nullptr) gameData.setActiveAction(make_shared<NoneAction>());
}

void ActionManager::addPossibleChecks(vector<shared_ptr<PossibleAction>>& possibleActions,
    ActionType recentType, bool isBigBlind) {
    
    switch(recentType) {
        // Edge case where it limps around preflop to the BB, and the BB should
        // have the option to check
        case ActionType::POST_BIG:
            if (!isBigBlind) break;
        case ActionType::NONE:
        case ActionType::CHECK:
        case ActionType::FOLD:
            possibleActions.push_back(make_shared<PossibleCheck>());
            break;
        default:
            break;
    }
}

void ActionManager::addPossibleBets( vector<shared_ptr<PossibleAction>>& possibleActions, 
    ActionType recentType, uint32_t playerStack, uint32_t otherBig) {

    switch(recentType) {
        case ActionType::NONE:
        case ActionType::CHECK:
        case ActionType::FOLD:
            // Max bet amount is the minimum of the player's stack and
            // the next biggest stack among other players
            possibleActions.push_back(make_shared<PossibleBet>(min(playerStack, otherBig)));

            // Player can only bet all-in if another player can at least all in call
            // this all in bet
            if (otherBig >= playerStack) possibleActions.push_back(make_shared<PossibleAllInBet>(playerStack));
        default:
            break;
    }
}

void ActionManager::addPossibleCalls(vector<shared_ptr<PossibleAction>>& possibleActions,
    ActionType recentType, uint32_t playerStack, uint32_t activeBet, bool isBigBlind) {

    switch(recentType) {
        // See above edge case - BB has the option to check rather than call
        case ActionType::POST_BIG:
            if (isBigBlind) break;
        case ActionType::BET:
        case ActionType::RAISE:
        case ActionType::ALL_IN_BET:
        case ActionType::ALL_IN_RAISE:
        case ActionType::POST_SMALL:
            // If player can match the active bet, normal call
            if (playerStack > activeBet) possibleActions.push_back(make_shared<PossibleCall>(activeBet));
            
            // If player can not match the active bet, must go all in -> side pot creation
            else possibleActions.push_back(make_shared<PossibleAllInCall>(playerStack));
            break;
        default:
            break;
    }
}

void ActionManager::addPossibleRaises(vector<shared_ptr<PossibleAction>>& possibleActions,
    ActionType recentType, uint32_t playerStack, uint32_t otherBig, uint32_t activebet) {
    
    uint32_t stdRaise = 2 * activebet;
    switch(recentType) {
        case ActionType::POST_SMALL:
        case ActionType::POST_BIG:
        case ActionType::BET:
        case ActionType::RAISE:
        case ActionType::ALL_IN_BET:
        case ActionType::ALL_IN_RAISE:
            // Early exit if the player can't raise the active bet
            if (playerStack <= activebet) break;

            // If std raise is less than the player's stack OR the next biggest stack,
            // treat as a normal raise, where the min is std raise and the max is the
            // min of the player's stack and the big stack among other players
            // Recall, you can only raise to what a player can call, so there's no point
            // allowing the big stack to raise all in to his chip count.
            if (stdRaise < playerStack || stdRaise < otherBig) {
                possibleActions.push_back(make_shared<PossibleRaise>(stdRaise, min(playerStack, otherBig)));
            }

            // If the player is NOT the big stack, has the option to raise all in
            if (otherBig >= playerStack) {
                possibleActions.push_back(make_shared<PossibleAllInRaise>(playerStack));
            }
            
            // If player is the big stack and the next biggest stack must go all in to call
            // the std raise, then the player can only raise to the amount of the next
            // biggest stack
            if (stdRaise >= otherBig && playerStack > otherBig) {
                possibleActions.push_back(make_shared<PossibleRaise>(otherBig, 0));
            }
            break;
        default:
            break;
    }
}

void ActionManager::addPossibleFolds(vector<shared_ptr<PossibleAction>>& possibleActions) {
    // Players should always have the option to fold regardless of the action
    possibleActions.push_back(make_shared<PossibleFold>());
}