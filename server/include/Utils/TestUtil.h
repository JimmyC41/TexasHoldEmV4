#ifndef TEST_UTIL_H
#define TEST_UTIL_H

#include "..//Entities/Player.h"
#include "../Entities/Board.h"
#include "../Entities/Card.h"
#include "../Entities/PossibleAction.h"
#include "../Services/DealerManager.h"
#include "../Services/HandRankManager.h"
#include "../Services/PlayerManager.h"
#include "../Services/PositionManager.h"
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
    // Manual Game Data Settters
    static void manualSetStreet(GameData& GameData, Street newStreet);
    static void manualClearActionTimeline(GameData& gameData);
    static void manualClearPots(GameData& gameData);
    static void manualSetPossibleAction(GameData& gameData, vector<shared_ptr<PossibleAction>> possible);
    static void dealCardsToPlayers(GameData& gameData, vector<string> idOrNames, vector<pair<Suit, Value>>& cards);
    
    static void manualAddPlayers(GameData& gameData, PlayerManager& playerManager, PositionManager& positionManager,
        vector<pair<string, size_t>> players);

    // Game Data Getters
    static vector<tuple<string, ActionType, size_t>> getActionTimelineVector(GameData& gameData);
    static vector<tuple<ActionType, PossibleAmounts>> getPossibleActionsVector(GameData& gameData);
    static vector<pair<size_t, vector<string>>> getPotsChipsAndNames(GameData& gameData);

    // General Helper Methods
    static bool isCardsUnique(const vector<Card>& cards);
    static vector<Card> aggregateDealtCards(GameData& gameData, DealerManager& dealer);
    static vector<Card> strToVectorOfCards(const string& stringOfCards);

    template <typename T>
    static vector<T> getSubset(vector<T>& vec, int start, int end) {
        return vector<T>(vec.begin() + start, vec.begin() + end);
    };

    // Game Services Helper

    // Deals players, calls hand evaluator to rank players and checks if the hand ranking is as expected
    static vector<string> evaluateHandsAndGetRankedNames(GameData& gameData, HandRankManager& handRankManager, vector<pair<Suit, Value>> cards);
};


#endif