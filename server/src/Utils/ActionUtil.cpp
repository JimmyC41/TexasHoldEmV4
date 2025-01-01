#include "../../include/Utils/ActionUtil.h"
#include "../../include/Entities/Actions/AllInBetAction.h"
#include "../../include/Entities/Actions/AllInCallAction.h"
#include "../../include/Entities/Actions/AllInRaiseAction.h"
#include "../../include/Entities/Actions/BetAction.h"
#include "../../include/Entities/Actions/CallAction.h"
#include "../../include/Entities/Actions/CheckAction.h"
#include "../../include/Entities/Actions/FoldAction.h"
#include "../../include/Entities/Actions/PostSmallAction.h"
#include "../../include/Entities/Actions/PostBigAction.h"
#include "../../include/Entities/Actions/RaiseAction.h"
#include "../../include/Entities/Actions/NoneAction.h"

shared_ptr<Action> ActionUtil::createAction(const string& idOrName, ActionType actionType, size_t amount){
    switch(actionType) {
        case ActionType::ALL_IN_BET: return make_shared<AllInBetAction>(idOrName, amount); break;
        case ActionType::ALL_IN_CALL: return make_shared<AllInCallAction>(idOrName, amount); break;
        case ActionType::ALL_IN_RAISE: return make_shared<AllInRaiseAction>(idOrName, amount); break;
        case ActionType::BET: return make_shared<BetAction>(idOrName, amount); break;
        case ActionType::CALL: return make_shared<CallAction>(idOrName, amount); break;
        case ActionType::CHECK: return make_shared<CheckAction>(idOrName); break;
        case ActionType::FOLD: return make_shared<FoldAction>(idOrName); break;
        case ActionType::RAISE: return make_shared<RaiseAction>(idOrName, amount); break;
        case ActionType::POST_SMALL: return make_shared<PostSmallAction>(idOrName, amount); break;
        case ActionType::POST_BIG: return make_shared<PostBigAction>(idOrName, amount); break;
        default: return make_shared<NoneAction>(); break;
    }
}

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