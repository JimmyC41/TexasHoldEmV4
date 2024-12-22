#include "../../include/Utils/TestUtil.h"
#include "../../include/Entities/Board.h"

// DealerTest
void createPlayersInGameData(GameData& gameData, vector<tuple<string, size_t, Position>> playersInfo) {
    for (const auto& info : playersInfo) {
        shared_ptr<Player> player = make_shared<Player>(get<0>(info), get<1>(info));
        gameData.addPlayer(player);
    }
}

// DealerTest
void clearPlayerHands(GameData& gameData) {
    for (auto& player : gameData.getPlayers()) player->clearHand();
}

// DealerTest
bool isCardsUnique(const vector<Card>& cards) {
    set<Card> uniqueCards(cards.begin(), cards.end());
    return uniqueCards.size() == cards.size();
}

// DealerTest
vector<Card> aggregateDealtCards(GameData& gameData, DealerManager& dealer) {
    vector<Card> cards;
    Board board = dealer.getBoard();

    for (auto& player : gameData.getPlayers()) {
        cards.insert(cards.end(), player->getHand().begin(), player->getHand().end());
    }
    cards.insert(cards.end(), board.getCommunityCards().begin(), board.getCommunityCards().end());

    return cards;
}

