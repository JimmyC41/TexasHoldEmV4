#ifndef ACTION_UTIL_H
#define ACTION_UTIL_H

#include "../Shared/GameData.h"
#include "GameUtil.h"

class ActionUtil { 
public:
    // Checks if a player can raise (i.e. initial chips > active bet)
    static bool canPlayerRaise(GameData& gameData, string idOrName);

    // Checks if a player can min raise (i.e. intial chips > 2 * active bet)
    static bool canPlayerMinRaise(GameData& gameData, string idOrName);

    // Checks if a player can bet all-in (i.e. initial chips < big stack among others)
    static bool canPlayerAllInBet(GameData& gameData, string idOrName);

    // Checks if a player can call the active bet without going all-in
    static bool canPlayerCallActiveBet(GameData& gameData, string idOrName);

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