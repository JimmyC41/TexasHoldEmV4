#include <gtest/gtest.h>
#include "../../include/Shared/Enums.h"
#include "../../include/Entities/Deck.h"
#include "../../include/Entities/Board.h"
#include "../../include/Services/DealerManager.h"
#include "../../include/Services/PlayerManager.h"
#include "../../include/Services/PositionManager.h"
#include "../../include/Utils/TestUtil.h"
#include "../../include/Utils/GameUtil.h"

#include <set>
#include <iostream>
#include <vector>
#include <tuple>

using namespace std;
using Position = Enums::Position;

class DealTest : public ::testing::Test {
protected:
    DealerManager dealer;
    PlayerManager playerManager;
    PositionManager positionManager;
    GameData gameData;

    const int numPlayers = 9;

    vector<pair<string, size_t>> playersInfo = 
    {
        {"P1", 100},
        {"P2", 200},
        {"P3", 300},
        {"P4", 400},
        {"P5", 500},
        {"P6", 600},
        {"P7", 700},
        {"P8", 800},
        {"P9", 900},
    };

    DealTest() : dealer(gameData), playerManager(gameData), positionManager(gameData) {
        playerManager.addNewPlayers(TestUtil::getSubset(playersInfo, 0, 9));
        positionManager.allocatePositions();
    }
    
    void TearDown() override {
        dealer.clearBoard();
        dealer.clearPlayerHands();
        dealer.resetDeck();
    }
};

TEST_F(DealTest, DealToPlayers) {
    dealer.dealGamePlayers();
    EXPECT_TRUE(GameUtil::isPlayersDealt(gameData));

    EXPECT_EQ(GameUtil::getNumPlayers(gameData), numPlayers);
    EXPECT_EQ(dealer.getDeckSize(), DECK_SIZE - 2*numPlayers);
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
    EXPECT_EQ(GameUtil::getNumPlayers(gameData), numPlayers);
}

TEST_F(DealTest, UniqueCardsDealt) {
    dealer.dealGamePlayers();
    EXPECT_TRUE(GameUtil::isPlayersDealt(gameData));

    dealer.dealBoard(3);
    dealer.dealBoard(1);
    dealer.dealBoard(1);

    vector<Card> allCards = TestUtil::aggregateDealtCards(gameData, dealer);
    EXPECT_TRUE(TestUtil::isCardsUnique(allCards));
}

TEST_F(DealTest, ResetDeck) {
    dealer.dealGamePlayers();
    EXPECT_TRUE(GameUtil::isPlayersDealt(gameData));

    dealer.dealBoard(5);
    int prevNumCards = dealer.getDeckSize();

    dealer.resetDeck();
    EXPECT_EQ(dealer.getDeckSize(), DECK_SIZE);
    EXPECT_NE(dealer.getDeckSize(), prevNumCards);
    EXPECT_EQ(GameUtil::getNumPlayers(gameData), numPlayers);
}

TEST_F(DealTest, ClearBoard) {
    dealer.dealBoard(3);
    dealer.clearBoard();
    EXPECT_EQ(dealer.getBoardSize(), 0);

    dealer.dealBoard(2);
    dealer.clearBoard();
    EXPECT_EQ(dealer.getBoardSize(), 0);

    dealer.dealBoard(1);
    dealer.clearBoard();
    EXPECT_EQ(dealer.getBoardSize(), 0);

    EXPECT_EQ(GameUtil::getNumPlayers(gameData), numPlayers);
}