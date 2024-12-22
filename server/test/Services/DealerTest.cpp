#include <gtest/gtest.h>
#include "../../include/Shared/Enums.h"
#include "../../include/Entities/Deck.h"
#include "../../include/Entities/Board.h"
#include "../../include/Services/DealerManager.h"
#include "../../include/Utils/TestUtil.h"

#include <set>
#include <iostream>
#include <vector>
#include <tuple>

using namespace std;
using Position = Enums::Position;

class DealTest : public ::testing::Test {
protected:
    Deck deck;
    Board board;
    DealerManager dealer;
    GameData gameData;
    vector<shared_ptr<Player>> gamePlayers;

    vector<tuple<string, size_t, Position>> playersInfo = 
    {
        {"P1", 500, Position::SMALL_BLIND},
        {"P2", 500, Position::BIG_BLIND},
        {"P3", 500, Position::MIDDLE},
        {"P4", 500, Position::CUT_OFF}
    };

    DealTest() : dealer(DealerManager::createDealerManager(gameData, deck, board)) {
        createPlayersInGameData(gameData, playersInfo);
        gameData.setPlayerPosition("P2", Position::BIG_BLIND);
        EXPECT_EQ(gameData.getNumPlayers(), 4);
    }
    
    void TearDown() override {
        dealer.resetDeck();
        dealer.resetBoard();
        clearPlayerHands(gameData);
    }
};

TEST_F(DealTest, DealToPlayers) {
    dealer.dealGamePlayers();
    EXPECT_TRUE(gameData.isPlayersDealt());

    EXPECT_EQ(dealer.getDeckSize(), DECK_SIZE - 8);
}

TEST_F(DealTest, DealToBoard) {
    dealer.dealBoard(3);
    EXPECT_EQ(dealer.getBoardSize(), 3);
    EXPECT_EQ(dealer.getDeckSize(), DECK_SIZE - 4);

    dealer.dealBoard(1);
    EXPECT_EQ(dealer.getBoardSize(), 4);
    EXPECT_EQ(dealer.getDeckSize(), DECK_SIZE - 6);

    dealer.dealBoard(1);
    EXPECT_EQ(dealer.getBoardSize(), 5);
    EXPECT_EQ(dealer.getDeckSize(), DECK_SIZE - 8);
}

TEST_F(DealTest, UniqueCardsDealt) {
    dealer.dealGamePlayers();
    EXPECT_TRUE(gameData.isPlayersDealt());

    dealer.dealBoard(3);
    dealer.dealBoard(1);
    dealer.dealBoard(1);

    vector<Card> allCards = aggregateDealtCards(gameData, dealer);
    EXPECT_TRUE(isCardsUnique(allCards));
}

TEST_F(DealTest, ResetDeck) {
    dealer.dealGamePlayers();
    EXPECT_TRUE(gameData.isPlayersDealt());

    dealer.dealBoard(5);
    int prevNumCards = dealer.getDeckSize();

    dealer.resetDeck();
    EXPECT_EQ(dealer.getDeckSize(), DECK_SIZE);
    EXPECT_NE(dealer.getDeckSize(), prevNumCards);
}

TEST_F(DealTest, ResetBoard) {
    dealer.dealBoard(3);
    dealer.resetBoard();
    EXPECT_EQ(dealer.getBoardSize(), 0);

    dealer.dealBoard(2);
    dealer.resetBoard();
    EXPECT_EQ(dealer.getBoardSize(), 0);

    dealer.dealBoard(1);
    dealer.resetBoard();
    EXPECT_EQ(dealer.getBoardSize(), 0);
}