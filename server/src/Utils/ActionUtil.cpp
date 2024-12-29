#include "../../include/Utils/ActionUtil.h"

bool ActionUtil::canPlayerRaise(GameData& gameData, string idOrName) {
    size_t playerStack = GameUtil::getPlayerInitialChips(gameData, idOrName);
    size_t activeBet = GameUtil::getActiveActionAmount(gameData);
    return (playerStack > activeBet);
}

bool ActionUtil::canPlayerMinRaise(GameData& gameData, string idOrName) {
    size_t playerStack = GameUtil::getPlayerInitialChips(gameData, idOrName);
    size_t activeBet = GameUtil::getActiveActionAmount(gameData);
    return (playerStack > 2 * activeBet);
}

bool ActionUtil::canPlayerAllInBet(GameData& gameData, string idOrName) {
    size_t playerStack = GameUtil::getPlayerInitialChips(gameData, idOrName);
    size_t bigStackAmongOthers = GameUtil::getBigStackAmongOthers(gameData, idOrName);
    return (bigStackAmongOthers >= playerStack);
}

bool ActionUtil::canPlayerCallActiveBet(GameData& gameData, string idOrName) {
    size_t playerStack = GameUtil::getPlayerInitialChips(gameData, idOrName);
    size_t activeBetAmount = GameUtil::getActiveActionAmount(gameData);
    return (playerStack > activeBetAmount);
}

size_t ActionUtil::getMinRaiseAmount(GameData& gameData, string idOrName) {
    size_t playerStack = GameUtil::getPlayerInitialChips(gameData, idOrName);
    size_t standardRaise = 2 * GameUtil::getActiveActionAmount(gameData);
    return min(playerStack, standardRaise);
}

size_t ActionUtil::getMaxBetAmount(GameData& gameData, string idOrName) {
    size_t playerStack = GameUtil::getPlayerInitialChips(gameData, idOrName);
    size_t bigStackAmongOthers = GameUtil::getBigStackAmongOthers(gameData, idOrName);
    return min(playerStack, bigStackAmongOthers);
}

 size_t ActionUtil::getCallAmount(GameData& gameData, string idOrName) { 
    size_t activeBetAmount = GameUtil::getActiveActionAmount(gameData);
    size_t playerStack = GameUtil::getPlayerInitialChips(gameData, idOrName);
    return min(playerStack, activeBetAmount);
 }

bool ActionUtil::isActionAggressive(ActionType actionType) {
    switch(actionType) {
        case ActionType::BET:
        case ActionType::ALL_IN_BET:
        case ActionType::ALL_IN_RAISE:
        case ActionType::RAISE:
        case ActionType::POST_SMALL:
        case ActionType::POST_BIG:
            return true;
        default:
            return false;
    }
}

PlayerStatus ActionUtil::inferStatusFromActionType(ActionType actionType) {
    switch(actionType) {
        case ActionType::FOLD: 
            return PlayerStatus::FOLDED;
        case ActionType::ALL_IN_BET:
        case ActionType::ALL_IN_RAISE:
            return PlayerStatus::ALL_IN_BET;
        case ActionType::ALL_IN_CALL: 
            return PlayerStatus::ALL_IN_CALL;
        default:
            return PlayerStatus::IN_HAND;
    }
}