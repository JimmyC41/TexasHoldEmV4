#ifndef PRINT_UTIL_H
#define PRINT_UTIL_H

#include "../Shared/GameData.h"
#include "../Services/PotManager.h"
#include "../include/Utils/GameUtil.h"
#include "../include/Utils/PotUtil.h"

using PlayerBetInfo = vector<tuple<string, size_t, PlayerStatus>>;

class PrintUtil {
public:
    static void printActionTimeline(GameData& gameData);
    static void printPlayers(GameData& gameData);
    static string printVectorCards(const vector<Card>& cards);
    static string positionToString(Position position);
    static string categoryToString(HandCategory category);
    static string actionTypeToString(ActionType type);
    static string playerStatusToString(PlayerStatus status);

    // PotManagerTest
    static void printPlayerBetsInPotManager(PlayerBetInfo& playerBetInfo);
};

#endif