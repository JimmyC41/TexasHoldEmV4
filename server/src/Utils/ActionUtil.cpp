#include "../../include/Utils/ActionUtil.h"

bool ActionUtil::canCurPlayerRaise(GameData& gameData) {
    size_t playerStack = gameData.getCurPlayer()->getInitialChips();
    size_t activeBet = GameUtil::getActiveActionAmount(gameData);
    return (playerStack > activeBet);
}

bool ActionUtil::canCurPlayerMinRaise(GameData& gameData) {
    size_t playerStack = gameData.getCurPlayer()->getInitialChips();
    size_t activeBet = GameUtil::getActiveActionAmount(gameData);
    return (playerStack > 2 * activeBet);
}

bool ActionUtil::canCurPlayerAllInBet(GameData& gameData) {
    size_t playerStack = gameData.getCurPlayer()->getInitialChips();
    size_t bigStackAmongOthers = GameUtil::getBigStackAmongOthers(gameData);
    return (bigStackAmongOthers >= playerStack);
}

bool ActionUtil::canCurPlayerCallActiveBet(GameData& gameData) {
    size_t playerStack = gameData.getCurPlayer()->getInitialChips();
    size_t activeBetAmount = GameUtil::getActiveActionAmount(gameData);
    return (playerStack > activeBetAmount);
}

size_t ActionUtil::getMinRaiseAmount(GameData& gameData) {
    size_t playerStack = gameData.getCurPlayer()->getInitialChips();
    size_t standardRaise = 2 * GameUtil::getActiveActionAmount(gameData);
    return min(playerStack, standardRaise);
}

size_t ActionUtil::getMaxBetAmount(GameData& gameData) {
    size_t playerStack = gameData.getCurPlayer()->getInitialChips();
    size_t bigStackAmongOthers = GameUtil::getBigStackAmongOthers(gameData);
    return min(playerStack, bigStackAmongOthers);
}

 size_t ActionUtil::getCallAmount(GameData& gameData) { 
    size_t activeBetAmount = GameUtil::getActiveActionAmount(gameData);
    size_t playerStack = gameData.getCurPlayer()->getInitialChips();
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