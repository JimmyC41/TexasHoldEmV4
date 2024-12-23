#include <gtest/gtest.h>
#include "../../include/Services/PlayerManager.h"
#include "../../include/Services/PositionManager.h"
#include "../../include/Utils/TestUtil.h"
#include "../../include/Utils/GameUtil.h"
#include "../../include/Utils/PrintUtil.h"

#include <vector>
using namespace std;

class PositionTest : public ::testing::Test {
protected:
    PlayerManager playerManager;
    PositionManager positionManager;
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

    PositionTest() : playerManager(gameData), positionManager(gameData) {}

    void TearDown() override {
        playerManager.removeAllPlayers();
    }
};


TEST_F(PositionTest, AllocatePositions) {
    // Add 2 players and allocate positions
    playerManager.addNewPlayers(TestUtil::getSubset(playersInfo, 0, 2));
    positionManager.allocatePositions();

    vector<Position> expected = {
        Position::SMALL_BLIND,
        Position::BIG_BLIND
    };
    EXPECT_EQ(GameUtil::getListOfPositions(gameData), expected);

    // Remove 1 player, 2 players and allocate positions
    playerManager.removeExistingPlayers({"P1"});
    playerManager.addNewPlayers(TestUtil::getSubset(playersInfo, 2, 4));
    positionManager.allocatePositions();

    expected = {
        Position::SMALL_BLIND,
        Position::BIG_BLIND,
        Position::UTG
    };
    EXPECT_EQ(GameUtil::getListOfPositions(gameData), expected);

    // Add 3 more players
    playerManager.addNewPlayers(TestUtil::getSubset(playersInfo, 4, 7));
    positionManager.allocatePositions();

    expected = {
        Position::SMALL_BLIND,
        Position::BIG_BLIND,
        Position::UTG,
        Position::UTG_1,
        Position::MIDDLE,
        Position::LOJACK
    };
    EXPECT_EQ(GameUtil::getListOfPositions(gameData), expected);
};

TEST_F(PositionTest, RotatePositionsFullTable) {
    // Add 9 players
    playerManager.addNewPlayers(TestUtil::getSubset(playersInfo, 0, 9));
    positionManager.allocatePositions();
    PrintUtil::printPlayers(gameData);

    // Rotate positions
    // Order of players should change, but same positions should remain
    positionManager.rotatePositions();
    PrintUtil::printPlayers(gameData);

    vector<Position> expectedPositions = {
        Position::SMALL_BLIND,
        Position::BIG_BLIND,
        Position::UTG,
        Position::UTG_1,
        Position::MIDDLE,
        Position::LOJACK,
        Position::HIJACK,
        Position::CUT_OFF,
        Position::DEALER
    };
    EXPECT_EQ(GameUtil::getListOfPositions(gameData), expectedPositions);

    vector<string> expectedNames = {
        "P9", "P1", "P2", "P3", "P4", "P5", "P6", "P7", "P8"
    };
    EXPECT_EQ(GameUtil::getListofNames(gameData), expectedNames);

    // Rotate positions again and check order
    positionManager.rotatePositions();
    PrintUtil::printPlayers(gameData);
    EXPECT_EQ(GameUtil::getListOfPositions(gameData), expectedPositions);
    expectedNames = {
        "P8", "P9", "P1", "P2", "P3", "P4", "P5", "P6", "P7"
    };
    EXPECT_EQ(GameUtil::getListofNames(gameData), expectedNames);

    // Rotate even times and check order
    for (int i = 0; i < 4; ++i) positionManager.rotatePositions();
    PrintUtil::printPlayers(gameData);

    EXPECT_EQ(GameUtil::getListOfPositions(gameData), expectedPositions);
    expectedNames = {
        "P4", "P5", "P6", "P7", "P8", "P9", "P1", "P2", "P3"
    };
    EXPECT_EQ(GameUtil::getListofNames(gameData), expectedNames);

    // Rotate odd times and check order
    for (int i = 0; i < 7; ++i) positionManager.rotatePositions();
    PrintUtil::printPlayers(gameData);

    EXPECT_EQ(GameUtil::getListOfPositions(gameData), expectedPositions);
    expectedNames = {
        "P6", "P7", "P8", "P9", "P1", "P2", "P3", "P4", "P5"
    };
    EXPECT_EQ(GameUtil::getListofNames(gameData), expectedNames);
}

TEST_F(PositionTest, RotatePositionsHeadsUp) {
    // Add 2 players
    playerManager.addNewPlayers(TestUtil::getSubset(playersInfo, 0, 2));
    positionManager.allocatePositions();

    PrintUtil::printPlayers(gameData);
    vector<Position> expectedPositions = {
        Position::SMALL_BLIND,
        Position::BIG_BLIND,
    };

    // Rotate once
    positionManager.rotatePositions();
    PrintUtil::printPlayers(gameData);

    EXPECT_EQ(GameUtil::getListOfPositions(gameData), expectedPositions);
    vector<string> expectedNames = {
        "P2", "P1"
    };
    EXPECT_EQ(GameUtil::getListofNames(gameData), expectedNames);

    // Rotate odd times and expect order to swap
    for (int i = 0; i < 7; ++i) positionManager.rotatePositions();
    PrintUtil::printPlayers(gameData);

    EXPECT_EQ(GameUtil::getListOfPositions(gameData), expectedPositions);
    expectedNames = {
        "P1", "P2"
    };
    EXPECT_EQ(GameUtil::getListofNames(gameData), expectedNames);

    // Rotate even times and expect order to remain the same
    for (int i = 0; i < 12; ++i) positionManager.rotatePositions();
    PrintUtil::printPlayers(gameData);

    EXPECT_EQ(GameUtil::getListOfPositions(gameData), expectedPositions);
    expectedNames = {
        "P1", "P2"
    };
    EXPECT_EQ(GameUtil::getListofNames(gameData), expectedNames);
};

TEST_F(PositionTest, GetEarlyPosition) {
    // Manually set the street to preflop
    TestUtil::manualSetStreet(gameData, Street::PRE_FLOP);

    // Add 6 players
    playerManager.addNewPlayers(TestUtil::getSubset(playersInfo, 0, 6));
    positionManager.allocatePositions();
    PrintUtil::printPlayers(gameData);

    // Early position should be UTG (P3)
    positionManager.setEarlyPositionToAct();
    string earlyPosition = GameUtil::getPlayerNameFromId(gameData, gameData.getCurPlayerId());
    EXPECT_EQ(earlyPosition, "P3");

    // Early position should be SB (P1) for flop, turn and river
    for (int street = static_cast<int>(Street::FLOP); 
        street <= static_cast<int>(Street::RIVER); ++street) {
            TestUtil::manualSetStreet(gameData, static_cast<Street>(street));
            positionManager.setEarlyPositionToAct();
            earlyPosition = GameUtil::getPlayerNameFromId(gameData, gameData.getCurPlayerId());
            EXPECT_EQ(earlyPosition, "P1");
    }
};

TEST_F(PositionTest, curPlayerUpdates) {
    // Setup: FLOP, 6 players
    TestUtil::manualSetStreet(gameData, Street::FLOP);
    playerManager.addNewPlayers(TestUtil::getSubset(playersInfo, 0, 6));
    positionManager.allocatePositions();
    positionManager.setEarlyPositionToAct();

    // Expect P1 is the current player to act
    string curPlayer = GameUtil::getPlayerNameFromId(gameData, gameData.getCurPlayerId());
    EXPECT_EQ(curPlayer, "P1");

    // Expect P2 is the next to act
    positionManager.updatePlayerToAct();
    curPlayer = GameUtil::getPlayerNameFromId(gameData, gameData.getCurPlayerId());
    EXPECT_EQ(curPlayer, "P2");

    // Expect P3, P4, P5, etc are the next to act
    vector<string> expectedPlayers = {"P3", "P4", "P5", "P6", "P1", "P2", "P3", "P4"};
    for (const auto& expectedPlayer : expectedPlayers) {
        positionManager.updatePlayerToAct();
        curPlayer = GameUtil::getPlayerNameFromId(gameData, gameData.getCurPlayerId());
        EXPECT_EQ(curPlayer, expectedPlayer);
    }
}