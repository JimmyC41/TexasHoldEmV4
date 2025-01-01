#ifndef ACTION_UTIL_H
#define ACTION_UTIL_H

#include "../Shared/GameData.h"
#include "GameUtil.h"

class ActionUtil { 
public:
    // Creates a new action object and returns a shared ptr
    static shared_ptr<Action> createAction(const string& idOrName, ActionType actionType, size_t amount = 0);

    // Finds the maximum amount that the player to act can bet given stack sizes
    static size_t getMaxBetAmount(GameData& gameData);

    // Checks if an Action Type is aggressive (i.e. requires other players to match the bet)
    // Aggressive actions include: Bet, All-In Bet, Raise, Post Small, Post Big
    static bool isActionAggressive(ActionType actionType);

    // Infers the player's status based on their action
    // E.g. If a player folds, their status changes from IN_HAND to FOLDED
    static PlayerStatus inferStatusFromActionType(ActionType actionType);
};

#endif