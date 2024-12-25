#ifndef PRINT_UTIL_H
#define PRINT_UTIL_H

#include "../Shared/GameData.h"

class PrintUtil {
public:
    static void printActionTimeline(GameData& gameData);
    static void printPlayers(GameData& gameData);
    static string printVectorCards(const vector<Card>& cards);
    static string positionToString(Position position);
    static string categoryToString(HandCategory category);
    static string actionTypeToString(ActionType type);
};

#endif