#include <gtest/gtest.h>
#include "../../include/Services/DealerManager.h"
#include "../../include/Services/PlayerManager.h"
#include "../../include/Services/PositionManager.h"
#include "../../include/Services/HandRankManager.h"
#include "../../include/Utils/TestUtil.h"
#include "../../include/Utils/GameUtil.h"

// Note: We should never be dealing cards to players outside
// of the Dealer class with the exception of Hand Rank testing!

// dealCardsToPlayer: Given a vector of Pair Suit values
// etches these Cards from the Deck and deals to the specified player

class HandRankTest : public ::testing::Test {
protected:
    DealerManager dealer;
    PlayerManager playerManager;
    PositionManager positionManager;
    HandRankManager handRankManager;
    GameData gameData;

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

    HandRankTest() : 
        dealer(gameData),
        playerManager(gameData),
        positionManager(gameData),
        handRankManager(gameData) 
    {}

    void TearDown() override {
        dealer.clearPlayerHands();
    }

    // Checks if the Hand Evaluator correctly evaluated the category
    // and best 5 cards for a given player
    void verifyHandEvaluation(
        GameData& gameData, string idOrName, 
        HandCategory expectedCategory, vector<Card> expectedBestFive) { 
            
        EXPECT_EQ(
            GameUtil::getPlayerHandCategory(gameData, idOrName),
            expectedCategory
        );

        EXPECT_EQ(
            GameUtil::getPlayerBestFiveCards(gameData, idOrName),
            expectedBestFive
        );
    }

    // Checks if the Hand Evaluator correctly ranked the players by hand strength
    void verifyHandRanking(GameData& gameData, vector<pair<Suit, Value>> cards, vector<string> expectedRanking) {
        // Create a vector of player names e.g. {"P1", "P2", "P3"}
        vector<string> playerNames;
        int numPlayers = (cards.size() - 5) / 2;
        for (int i = 1; i <= numPlayers; ++i) playerNames.push_back("P" + to_string(i));
        
        // Deal the board cards to each player
        vector<pair<Suit, Value>> board = TestUtil::getSubset(cards, 0, 5);
        TestUtil::dealCardsToPlayers(gameData, playerNames, board);

        // Deal each player's hole cards
        size_t offset = 5;
        for (int i = 0; i < numPlayers; ++i) {
            vector<pair<Suit, Value>> holeCards = TestUtil::getSubset(cards, offset, offset + 2);
            TestUtil::dealCardsToPlayers(gameData, {playerNames[i]}, holeCards);
            offset += 2;
        }

        handRankManager.evaluateRankedIds();
        EXPECT_EQ(GameUtil::getRankedNames(gameData), expectedRanking);
    }
};

TEST_F(HandRankTest, RoyalFlush) {
    playerManager.addNewPlayers(TestUtil::getSubset(playersInfo, 0, 1));

    vector<pair<Suit, Value>> royalFlush = {
        {Suit::HEARTS, Value::ACE},
        {Suit::DIAMONDS, Value::QUEEN},
        {Suit::SPADES, Value::ACE},
        {Suit::SPADES, Value::QUEEN},
        {Suit::SPADES, Value::JACK},
        {Suit::SPADES, Value::TEN},
        {Suit::SPADES, Value::KING},
    };

    TestUtil::dealCardsToPlayers(gameData, {"P1"}, royalFlush);
    handRankManager.evaluateRankedIds();

    verifyHandEvaluation(gameData,
        "P1",
        HandCategory::ROYAL_FLUSH,
        TestUtil::strToVectorOfCards("AsKsQsJsTs")
    );

};

TEST_F(HandRankTest, StraightFlush) {
    playerManager.addNewPlayers(TestUtil::getSubset(playersInfo, 0, 1));

    vector<pair<Suit, Value>> straightFlush = {
        {Suit::HEARTS, Value::ACE},
        {Suit::DIAMONDS, Value::QUEEN},
        {Suit::SPADES, Value::TWO},
        {Suit::SPADES, Value::ACE},
        {Suit::SPADES, Value::THREE},
        {Suit::SPADES, Value::FIVE},
        {Suit::SPADES, Value::FOUR},
    };

    TestUtil::dealCardsToPlayers(gameData, {"P1"}, straightFlush);
    handRankManager.evaluateRankedIds();

    verifyHandEvaluation(gameData,
        "P1",
        HandCategory::STRAIGHT_FLUSH,
        TestUtil::strToVectorOfCards("5s4s3s2sAs")
    );

};

TEST_F(HandRankTest, FourOfAKind) {
    playerManager.addNewPlayers(TestUtil::getSubset(playersInfo, 0, 1));

    vector<pair<Suit, Value>> quads = {
        {Suit::SPADES, Value::ACE},
        {Suit::DIAMONDS, Value::QUEEN},
        {Suit::SPADES, Value::QUEEN},
        {Suit::CLUBS, Value::QUEEN},
        {Suit::HEARTS, Value::QUEEN},
        {Suit::SPADES, Value::FIVE},
        {Suit::SPADES, Value::FOUR},
    };

    TestUtil::dealCardsToPlayers(gameData, {"P1"}, quads);
    handRankManager.evaluateRankedIds();

    verifyHandEvaluation(gameData,
        "P1",
        HandCategory::FOUR_OF_A_KIND,
        TestUtil::strToVectorOfCards("QdQsQcQhAs")
    );

};

TEST_F(HandRankTest, FullHouse) {
    playerManager.addNewPlayers(TestUtil::getSubset(playersInfo, 0, 1));

    vector<pair<Suit, Value>> book = {
        {Suit::SPADES, Value::ACE},
        {Suit::DIAMONDS, Value::FIVE},
        {Suit::HEARTS, Value::ACE},
        {Suit::HEARTS, Value::TWO},
        {Suit::DIAMONDS, Value::ACE},
        {Suit::CLUBS, Value::FOUR},
        {Suit::SPADES, Value::FIVE}
    };

    TestUtil::dealCardsToPlayers(gameData, {"P1"}, book);
    handRankManager.evaluateRankedIds();

    verifyHandEvaluation(gameData,
        "P1",
        HandCategory::FULL_HOUSE,
        TestUtil::strToVectorOfCards("AsAhAd5d5s")
    );

};

TEST_F(HandRankTest, Straight) {
    playerManager.addNewPlayers(TestUtil::getSubset(playersInfo, 0, 1));

    vector<pair<Suit, Value>> straight = {
        {Suit::SPADES, Value::TWO},
        {Suit::HEARTS, Value::THREE},
        {Suit::SPADES, Value::FOUR},
        {Suit::SPADES, Value::FIVE},
        {Suit::DIAMONDS, Value::ACE},
        {Suit::HEARTS, Value::SIX},
        {Suit::SPADES, Value::SEVEN}
    };

    TestUtil::dealCardsToPlayers(gameData, {"P1"}, straight);
    handRankManager.evaluateRankedIds();

    verifyHandEvaluation(gameData,
        "P1",
        HandCategory::STRAIGHT,
        TestUtil::strToVectorOfCards("7s6h5s4s3h")
    );

};

TEST_F(HandRankTest, ThreeOfAKind) {
    playerManager.addNewPlayers(TestUtil::getSubset(playersInfo, 0, 1));

    vector<pair<Suit, Value>> trips = {
        {Suit::SPADES, Value::ACE},
        {Suit::HEARTS, Value::KING},
        {Suit::SPADES, Value::FOUR},
        {Suit::SPADES, Value::FIVE},
        {Suit::DIAMONDS, Value::ACE},
        {Suit::HEARTS, Value::ACE},
        {Suit::SPADES, Value::SEVEN}
    };

    TestUtil::dealCardsToPlayers(gameData, {"P1"}, trips);
    handRankManager.evaluateRankedIds();

    verifyHandEvaluation(gameData,
        "P1",
        HandCategory::THREE_OF_A_KIND,
        TestUtil::strToVectorOfCards("AsAdAhKh7s")
    );

};

TEST_F(HandRankTest, TwoPair) {
    playerManager.addNewPlayers(TestUtil::getSubset(playersInfo, 0, 1));

    vector<pair<Suit, Value>> twoPair = {
        {Suit::SPADES, Value::ACE},
        {Suit::HEARTS, Value::KING},
        {Suit::SPADES, Value::QUEEN},
        {Suit::SPADES, Value::FIVE},
        {Suit::DIAMONDS, Value::ACE},
        {Suit::CLUBS, Value::KING},
        {Suit::SPADES, Value::SEVEN}
    };

    TestUtil::dealCardsToPlayers(gameData, {"P1"}, twoPair);
    handRankManager.evaluateRankedIds();

    verifyHandEvaluation(gameData,
        "P1",
        HandCategory::TWO_PAIR,
        TestUtil::strToVectorOfCards("AsAdKhKcQs")
    );

};

TEST_F(HandRankTest, OnePair) {
    playerManager.addNewPlayers(TestUtil::getSubset(playersInfo, 0, 1));

    vector<pair<Suit, Value>> onePair = {
        {Suit::HEARTS, Value::EIGHT},
        {Suit::HEARTS, Value::KING},
        {Suit::SPADES, Value::QUEEN},
        {Suit::SPADES, Value::FIVE},
        {Suit::DIAMONDS, Value::EIGHT},
        {Suit::CLUBS, Value::JACK},
        {Suit::SPADES, Value::SEVEN}
    };

    TestUtil::dealCardsToPlayers(gameData, {"P1"}, onePair);
    handRankManager.evaluateRankedIds();

    verifyHandEvaluation(gameData,
        "P1",
        HandCategory::ONE_PAIR,
        TestUtil::strToVectorOfCards("8h8dKhQsJc")
    );

};

TEST_F(HandRankTest, HighCard) {
    playerManager.addNewPlayers(TestUtil::getSubset(playersInfo, 0, 1));

    vector<pair<Suit, Value>> highCard = {
        {Suit::HEARTS, Value::THREE},
        {Suit::DIAMONDS, Value::ACE},
        {Suit::CLUBS, Value::FOUR},
        {Suit::SPADES, Value::KING},
        {Suit::HEARTS, Value::SIX},
        {Suit::DIAMONDS, Value::JACK},
        {Suit::CLUBS, Value::EIGHT}
    };

    TestUtil::dealCardsToPlayers(gameData, {"P1"}, highCard);
    handRankManager.evaluateRankedIds();

    verifyHandEvaluation(gameData,
        "P1",
        HandCategory::HIGH_CARD,
        TestUtil::strToVectorOfCards("AdKsJd8c6h")
    );

};

TEST_F(HandRankTest, TooFewCards) {
    playerManager.addNewPlayers(TestUtil::getSubset(playersInfo, 0, 1));

    vector<pair<Suit, Value>> tooFewCards = {
        {Suit::HEARTS, Value::THREE},
        {Suit::DIAMONDS, Value::ACE},
        {Suit::CLUBS, Value::FOUR},
        {Suit::SPADES, Value::KING},
    };

    TestUtil::dealCardsToPlayers(gameData, {"P1"}, tooFewCards);
    handRankManager.evaluateRankedIds();

    verifyHandEvaluation(gameData,
        "P1",
        HandCategory::NONE,
        TestUtil::strToVectorOfCards("AdKs4c3h")
    );

};

TEST_F(HandRankTest, FullHouseTie) {
    playerManager.addNewPlayers(TestUtil::getSubset(playersInfo, 0, 2));

    vector<pair<Suit, Value>> cards = {
        // Board
        {Suit::HEARTS, Value::ACE},
        {Suit::DIAMONDS, Value::ACE},
        {Suit::SPADES, Value::QUEEN},
        {Suit::DIAMONDS, Value::THREE},
        {Suit::HEARTS, Value::THREE},
        // Player 1
        {Suit::SPADES, Value::ACE},
        {Suit::CLUBS, Value::QUEEN},
        // Player 2
        {Suit::DIAMONDS, Value::QUEEN},
        {Suit::HEARTS, Value::QUEEN}
    };

    verifyHandRanking(gameData, cards, vector<string>{"P1", "P2"});
};

TEST_F(HandRankTest, FlushTie) {
    playerManager.addNewPlayers(TestUtil::getSubset(playersInfo, 0, 4));

    vector<pair<Suit, Value>> cards = {
        // Board
        {Suit::DIAMONDS, Value::TWO},
        {Suit::DIAMONDS, Value::THREE},
        {Suit::HEARTS, Value::FOUR},
        {Suit::HEARTS, Value::FIVE},
        {Suit::HEARTS, Value::SIX},
        // Player 1
        {Suit::HEARTS, Value::ACE},
        {Suit::HEARTS, Value::KING},
        // Player 2
        {Suit::HEARTS, Value::QUEEN},
        {Suit::HEARTS, Value::JACK},
        // Player 3
        {Suit::HEARTS, Value::SEVEN},
        {Suit::HEARTS, Value::EIGHT},
        //Player 4
        {Suit::HEARTS, Value::NINE},
        {Suit::HEARTS, Value::TEN}
    };

    verifyHandRanking(gameData, cards, vector<string>{"P3", "P1", "P2", "P4"});
};

TEST_F(HandRankTest, StraightTie) {
    playerManager.addNewPlayers(TestUtil::getSubset(playersInfo, 0, 3));

    vector<pair<Suit, Value>> cards = {
        // Board
        {Suit::DIAMONDS, Value::ACE},
        {Suit::DIAMONDS, Value::KING},
        {Suit::HEARTS, Value::FIVE},
        {Suit::HEARTS, Value::SIX},
        {Suit::HEARTS, Value::SEVEN},
        // Player 1
        {Suit::SPADES, Value::EIGHT},
        {Suit::SPADES, Value::NINE},
        // Player 2
        {Suit::CLUBS, Value::FOUR},
        {Suit::CLUBS, Value::EIGHT},
        // Player 3
        {Suit::HEARTS, Value::EIGHT},
        {Suit::HEARTS, Value::NINE}
    };

    verifyHandRanking(gameData, cards, vector<string>{"P3", "P1", "P2"});
};

TEST_F(HandRankTest, ThreeOfAKindTie) {
    playerManager.addNewPlayers(TestUtil::getSubset(playersInfo, 0, 2));

    vector<pair<Suit, Value>> cards = {
        // Board
        {Suit::CLUBS, Value::THREE},
        {Suit::SPADES, Value::ACE},
        {Suit::HEARTS, Value::SIX},
        {Suit::DIAMONDS, Value::SIX},
        {Suit::CLUBS, Value::TWO},
        // Player 1
        {Suit::SPADES, Value::SIX},
        {Suit::HEARTS, Value::QUEEN},
        // Player 2
        {Suit::CLUBS, Value::SIX},
        {Suit::HEARTS, Value::KING}
    };

    verifyHandRanking(gameData, cards, vector<string>{"P2", "P1"});
};

TEST_F(HandRankTest, TwoPairTie) {
    playerManager.addNewPlayers(TestUtil::getSubset(playersInfo, 0, 3));

    vector<pair<Suit, Value>> cards = {
        // Boards
        {Suit::CLUBS, Value::ACE},
        {Suit::SPADES, Value::ACE},
        {Suit::CLUBS, Value::TWO},
        {Suit::CLUBS, Value::THREE},
        {Suit::CLUBS, Value::FOUR},
        // Player 1
        {Suit::DIAMONDS, Value::FOUR},
        {Suit::DIAMONDS, Value::KING},
        // Player 2
        {Suit::HEARTS, Value::FOUR},
        {Suit::DIAMONDS, Value::QUEEN},
        // Player 3
        {Suit::SPADES, Value::FOUR},
        {Suit::DIAMONDS, Value::JACK},
    };

    verifyHandRanking(gameData, cards, vector<string>{"P1", "P2", "P3"});
};

TEST_F(HandRankTest, ComplexHandRanking) {
    playerManager.addNewPlayers(TestUtil::getSubset(playersInfo, 0, 3));

    vector<pair<Suit, Value>> cards = {
        // Boards
        {Suit::CLUBS, Value::FOUR},
        {Suit::CLUBS, Value::FIVE},
        {Suit::CLUBS, Value::SIX},
        {Suit::SPADES, Value::SEVEN},
        {Suit::SPADES, Value::ACE},
        // Player 1
        {Suit::CLUBS, Value::TWO},
        {Suit::CLUBS, Value::THREE},
        // Player 2
        {Suit::CLUBS, Value::KING},
        {Suit::CLUBS, Value::QUEEN},
        // Player 3
        {Suit::HEARTS, Value::FOUR},
        {Suit::HEARTS, Value::FIVE},
        // Player 4
        {Suit::HEARTS, Value::EIGHT},
        {Suit::HEARTS, Value::NINE},
        // Player 5
        {Suit::HEARTS, Value::ACE},
        {Suit::HEARTS, Value::TWO},
        // Player 6
        {Suit::DIAMONDS, Value::ACE},
        {Suit::HEARTS, Value::TEN},
        // Player 7
        {Suit::CLUBS, Value::ACE},
        {Suit::HEARTS, Value::SEVEN},
        // Player 8
        {Suit::CLUBS, Value::JACK},
        {Suit::CLUBS, Value::TEN},
        // Player 9
        {Suit::DIAMONDS, Value::FOUR},
        {Suit::SPADES, Value::FOUR}
    };

    verifyHandRanking(gameData, cards,
        vector<string>{"P1", "P2", "P8", "P4", "P9", "P7", "P3", "P6", "P5"});
};