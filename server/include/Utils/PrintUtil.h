#ifndef PRINT_UTIL_H
#define PRINT_UTIL_H

#include "../Shared/GameData.h"
#include "../Services/PotManager.h"
#include "../Entities/PossibleAction.h"
#include "GameUtil.h"
#include "PotUtil.h"

using PlayerBetInfo = vector<tuple<string, uint32_t, PlayerStatus>>;

class PrintUtil {
public:
    // Game State 
    static void printActionTimeline(GameData& gameData);
    static void printAllCards(GameData& gameData);
    static void printPlayers(GameData& gameData);
    static void printPots(GameData& gameData);
    static void printPossibleActionsForCurPlayer(GameData& gameData);
    static void printClientAction(pair<ActionType, uint32_t> action);

    // String Helpers
    static string printVectorCards(const vector<Card>& cards);
    static string positionToString(Position position);
    static string categoryToString(HandCategory category);
    static string actionTypeToString(ActionType type);
    static string playerStatusToString(PlayerStatus status);
    static string printVectorString(const vector<string>& strings);
    static string streetToString(Street& street);

    // PotManagerTest
    static void printPlayerBetsInPotManager(PlayerBetInfo& playerBetInfo);
};

#endif