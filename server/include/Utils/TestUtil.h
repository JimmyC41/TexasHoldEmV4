#ifndef TEST_UTIL_H
#define TEST_UTIL_H

#include "..//Entities/Player.h"
#include "../Entities/Board.h"
#include "../Entities/Card.h"
#include "../Entities/PossibleAction.h"
#include "../Services/DealerManager.h"
#include "../Utils/CardUtil.h"
#include "../Shared/GameData.h"
#include <string>
#include <memory>
#include <set>
#include <variant>
using namespace std;

class PossibleAction;

using PossibleAmounts = variant<monostate, size_t, tuple<size_t, size_t>>;

class TestUtil {
public:
    template <typename T>
    static vector<T> getSubset(vector<T>& vec, int start, int end) {
        return vector<T>(vec.begin() + start, vec.begin() + end);
    };

    static void manualSetStreet(GameData& GameData, Street newStreet);
    static void manualClearActionTimeline(GameData& gameData);
    static bool isCardsUnique(const vector<Card>& cards);
    static vector<Card> aggregateDealtCards(GameData& gameData, DealerManager& dealer);
    static void dealCardsToPlayers(GameData& gameData, vector<string> idOrNames, vector<pair<Suit, Value>>& cards);
    static vector<Card> strToVectorOfCards(const string& stringOfCards);
    static vector<tuple<string, ActionType, size_t>> getActionTimelineVector(GameData& gameData);
    static vector<tuple<ActionType, PossibleAmounts>> getPossibleActionsVector(GameData& gameData);
};


#endif