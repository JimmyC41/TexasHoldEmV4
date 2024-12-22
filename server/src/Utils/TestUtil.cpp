#include "../../include/Utils/TestUtil.h"
#include "../../include/Entities/Board.h"

void TestUtil::createPlayersInGameData(GameData& gameData, vector<tuple<string, size_t, Position>> playersInfo) {
    for (const auto& info : playersInfo) {
        shared_ptr<Player> player = make_shared<Player>(get<0>(info), get<1>(info));
        gameData.addPlayer(player);
    }
}

void TestUtil::clearPlayerHands(GameData& gameData) {
    for (auto& player : gameData.getPlayers()) player->clearHand();
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

