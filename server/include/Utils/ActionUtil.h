#ifndef ACTION_UTIL_H
#define ACTION_UTIL_H

#include "../Shared/GameData.h"
#include "GameUtil.h"

class ActionUtil { 
public:
    // Checks if the player to act can raise (i.e. initial chips > active bet)
    static bool canCurPlayerRaise(GameData& gameData);

    // Checks if the player to act can min raise (i.e. intial chips > 2 * active bet)
    static bool canCurPlayerMinRaise(GameData& gameData);

    // Checks if the player to act can bet all-in (i.e. initial chips < big stack among others)
    static bool canCurPlayerAllInBet(GameData& gameData);

    // Checks if the player to act can call the active bet without going all-in
    static bool canCurPlayerCallActiveBet(GameData& gameData);

    // Finds the minimum valid raise for the player to act given stack sizes
    static size_t getMinRaiseAmount(GameData& gameData);

    // Finds the maximum amount that the player to act can bet given stack sizes
    static size_t getMaxBetAmount(GameData& gameData);

    // Finds the amount that the player to act must call given their relative stack size
    static size_t getCallAmount(GameData& gameData);

    // Checks if an Action Type is aggressive (i.e. requires other players to match the bet)
    // Aggressive actions include: Bet, All-In Bet, Raise, Post Small, Post Big
    static bool isActionAggressive(ActionType actionType);

    // Infers the player's status based on their action
    // E.g. If a player folds, their status changes from IN_HAND to FOLDED
    static PlayerStatus inferStatusFromActionType(ActionType actionType);
};

#endif