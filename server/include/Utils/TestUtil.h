#ifndef TEST_UTIL_H
#define TEST_UTIL_H

#include "..//Entities/Player.h"
#include "../Entities/Board.h"
#include "../Entities/Card.h"
#include "../Services/DealerManager.h"
#include "../Utils/CardUtil.h"
#include "../Shared/GameData.h"
#include <string>
#include <memory>
#include <set>
using namespace std;

class TestUtil {
public:
    template <typename T1, typename T2>
    static vector<pair<T1, T2>> getSubset(vector<pair<T1, T2>>& vec, int start, int end) {
        return vector<pair<T1, T2>>(vec.begin() + start, vec.begin() + end);
    };

    static void manualSetStreet(GameData& GameData, Street newStreet);
    static bool isCardsUnique(const vector<Card>& cards);
    static vector<Card> aggregateDealtCards(GameData& gameData, DealerManager& dealer);
    static void dealCardsToPlayers(GameData& gameData, vector<string> idOrNames, vector<pair<Suit, Value>>& cards);
    static vector<Card> strToVectorOfCards(const string& stringOfCards);
};


#endif