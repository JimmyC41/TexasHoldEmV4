#ifndef TEST_UTIL_H
#define TEST_UTIL_H

#include "../../include/Entities/Player.h"
#include "../../include/Entities/Board.h"
#include "../../include/Entities/Card.h"
#include "../../include/Services/DealerManager.h"
#include <string>
#include <memory>
#include <set>
using namespace std;

class TestUtil {
public:
    static vector<pair<string, size_t>> getSubset(vector<pair<string, size_t>>& vec, int start, int end);
    static bool isCardsUnique(const vector<Card>& cards);
    static vector<Card> aggregateDealtCards(GameData& gameData, DealerManager& dealer);
};


#endif