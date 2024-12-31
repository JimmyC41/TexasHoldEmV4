#include "../../include/Utils/ActionUtil.h"

size_t ActionUtil::getMaxBetAmount(GameData& gameData) {
    size_t playerStack = gameData.getCurPlayer()->getInitialChips();
    size_t bigStackAmongOthers = GameUtil::getBigStackAmongOthers(gameData);
    return min(playerStack, bigStackAmongOthers);
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