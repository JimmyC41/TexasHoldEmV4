#include "../../include/Utils/TestUtil.h"
#include "../../include/Entities/Board.h"

void TestUtil::manualSetStreet(GameData& GameData, Street newStreet) {
    GameData.setCurStreet(newStreet);
}

vector<pair<string, size_t>> TestUtil::getSubset(
    vector<pair<string, size_t>>& vec, int start, int end
) {
    return vector<pair<string, size_t>>(vec.begin() + start, vec.begin() + end);
}

bool TestUtil::isCardsUnique(const vector<Card>& cards) {
    set<Card> uniqueCards(cards.begin(), cards.end());
    return uniqueCards.size() == cards.size();
}

vector<Card> TestUtil::aggregateDealtCards(GameData& gameData, DealerManager& dealer) {
    vector<Card> cards;
    Board board = dealer.getBoard();

    for (auto& player : gameData.getPlayers()) {
        cards.insert(cards.end(), player->getHand().begin(), player->getHand().end());
    }
    cards.insert(cards.end(), board.getCommunityCards().begin(), board.getCommunityCards().end());

    return cards;
}

