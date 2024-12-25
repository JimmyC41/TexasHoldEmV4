#ifndef ACTION_UTIL_H
#define ACTION_UTIL_H

#include "../Shared/GameData.h"
#include "GameUtil.h"

class ActionUtil { 
public:
    // Verifies if a player can raise (i.e. initial chips > active bet to match)
    static size_t canPlayerRaise(GameData& gameData, string idOrName);

    // Finds the minimum valid raise for a player given stack sizes
    static size_t getMinRaiseAmount(GameData& gameData, string idOrName);

    // Finds the maximum amount that a player can bet given stack sizes
    static size_t getMaxBetAmount(GameData& gameData, string idOrName);

    // Finds the amount that a player must call given their relative stack size
    static size_t getCallAmount(GameData& gameData, string idOrName);

    // Checks if an Action Type is aggressive (i.e. requires other players to match the bet)
    // Aggressive actions include: Bet, All-In Bet, Raise, Post Small, Post Big
    static bool isActionAggressive(ActionType actionType);

    // Infers the player's status based on their action
    // E.g. If a player folds, their status changes from IN_HAND to FOLDED
    static PlayerStatus inferStatusFromActionType(ActionType actionType);
};

#endif