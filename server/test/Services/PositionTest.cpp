#include <gtest/gtest.h>
#include "../../include/Services/PlayerManager.h"
#include "../../include/Services/PositionManager.h"
#include "../../include/Services/ActionManager.h"
#include "../../include/Utils/TestUtil.h"
#include "../../include/Utils/GameUtil.h"
#include "../../include/Utils/PrintUtil.h"

#include <vector>
using namespace std;

class PositionTest : public ::testing::Test {
protected:
    unique_ptr<PlayerManager> playerManager;
    unique_ptr<PositionManager> positionManager;
    unique_ptr<ActionManager> actionManager;
    unique_ptr<GameData> gameData;

    vector<pair<string, uint32_t>> playersInfo = 
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

    vector<Position> allPositions = {
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

    void SetUp() override {
        gameData = make_unique<GameData>();
        playerManager = make_unique<PlayerManager>(*gameData);
        positionManager = make_unique<PositionManager>(*gameData);
        actionManager = make_unique<ActionManager>(*gameData);

        TestUtil::manualSetStreet(*gameData, Street::FLOP);
    }

    void TearDown() override {
        gameData->reset();
    }

    // For some 'n' adds players 1 to n and allocates positions
    void playerSetup(int n) {
        playerManager->addNewPlayers(TestUtil::getSubset(playersInfo, 0, n));
        positionManager->allocatePositions();
        positionManager->setEarlyPositionToAct();

        PrintUtil::printPlayers(*gameData);
    }

    void verifyPositionsAfterPlayerAddition(
        vector<pair<string, uint32_t>> newPlayers,
        vector<Position> expectedPositions) {
        
        playerManager->addNewPlayers(newPlayers);
        positionManager->allocatePositions();

        PrintUtil::printPlayers(*gameData);

        EXPECT_EQ(GameUtil::getListOfPositions(*gameData), expectedPositions);
    }

    void verifyPositionsAfterPlayerRemoval(
        vector<string> playersToRemove,
        vector<Position> expectedPositions) {
        
        playerManager->removeExistingPlayers(playersToRemove);
        positionManager->allocatePositions();

        PrintUtil::printPlayers(*gameData);

        EXPECT_EQ(GameUtil::getListOfPositions(*gameData), expectedPositions);
    }

    void verifyPositionsAfterNRotations(
        int numRotations,
        vector<Position> expectedPositions, 
        vector<string> expectedOrderOfNames) {
        
        for (int i = 0; i < numRotations; ++i) positionManager->rotatePositions();

        PrintUtil::printPlayers(*gameData);

        EXPECT_EQ(GameUtil::getListOfPositions(*gameData), expectedPositions);
        EXPECT_EQ(GameUtil::getListofNames(*gameData), expectedOrderOfNames);
    }

    void addActionAndUpdateCurPlayer(ActionType type, uint32_t amount) {
        actionManager->addNewAction(gameData->getCurPlayer()->getId(), type, amount);
        positionManager->updatePlayerToAct();
    }

    void verifyEarlyPositionToAct(Street street, string expectedEarlyPosition) {
        TestUtil::manualSetStreet(*gameData, street);
        positionManager->setEarlyPositionToAct();
        verifyCurPlayerAndUpdate(expectedEarlyPosition);
    }

    void verifyCurPlayerAndUpdate(string expectedName) {
        string curPlayer = GameUtil::getPlayerNameFromId(*gameData, gameData->getCurPlayer()->getId());
        EXPECT_EQ(curPlayer, expectedName);
        positionManager->updatePlayerToAct();
    }
};

TEST_F(PositionTest, AllocatePositions) {
    playerSetup(2);
    EXPECT_EQ(GameUtil::getListOfPositions(*gameData), TestUtil::getSubset(allPositions, 0, 2));

    verifyPositionsAfterPlayerRemoval(
        {"P1"}, 
        TestUtil::getSubset(allPositions, 1, 2)); // Remove SB - expect to only have BB

    verifyPositionsAfterPlayerAddition(
        TestUtil::getSubset(playersInfo, 2, 4),
        TestUtil::getSubset(allPositions, 0, 3));
    
    verifyPositionsAfterPlayerAddition(
        TestUtil::getSubset(playersInfo, 4, 7),
        TestUtil::getSubset(allPositions, 0, 6));
};

TEST_F(PositionTest, RotatePositionsFullTable) {
    // Add 9 players
    playerSetup(9);

    verifyPositionsAfterNRotations(1, TestUtil::getSubset(allPositions, 0, 9),
        vector<string>({"P9", "P1", "P2", "P3", "P4", "P5", "P6", "P7", "P8"}));

    verifyPositionsAfterNRotations(1, TestUtil::getSubset(allPositions, 0, 9),
        vector<string>({"P8", "P9", "P1", "P2", "P3", "P4", "P5", "P6", "P7"}));

    verifyPositionsAfterNRotations(2, TestUtil::getSubset(allPositions, 0, 9),
        vector<string>({"P6", "P7", "P8", "P9", "P1", "P2", "P3", "P4", "P5"}));

    verifyPositionsAfterNRotations(3, TestUtil::getSubset(allPositions, 0, 9),
        vector<string>({"P3", "P4", "P5", "P6", "P7", "P8", "P9", "P1", "P2"}));
}

TEST_F(PositionTest, RotatePositionsHeadsUp) {
    // Add 2 players
    playerManager->addNewPlayers(TestUtil::getSubset(playersInfo, 0, 2));
    positionManager->allocatePositions();

    verifyPositionsAfterNRotations(1, TestUtil::getSubset(allPositions, 0, 2),
        vector<string>({"P2", "P1"}));
    
    verifyPositionsAfterNRotations(1, TestUtil::getSubset(allPositions, 0, 2),
        vector<string>({"P1", "P2"}));

    // Rotate odd times and expect order to swap
    verifyPositionsAfterNRotations(3, TestUtil::getSubset(allPositions, 0, 2),
        vector<string>({"P2", "P1"}));
};

TEST_F(PositionTest, GetEarlyPosition) {
    playerSetup(6);

    verifyEarlyPositionToAct(Street::PRE_FLOP, "P3");
    verifyEarlyPositionToAct(Street::FLOP, "P1");
    verifyEarlyPositionToAct(Street::TURN, "P1");
    verifyEarlyPositionToAct(Street::RIVER, "P1");
};

TEST_F(PositionTest, curPlayerUpdates) {
    playerSetup(6);

    for (int i = 0; i < 1000; i++) {
        int expectedNum = (i % 6) + 1;
        string expectedPlayer = "P" + to_string(expectedNum);
        verifyCurPlayerAndUpdate(expectedPlayer);
    }
}

TEST_F(PositionTest, curPlayerUpdatesWithFolds) {
    playerSetup(4);

    // Add the following actions:
    // P1 - Bet, 5
    // P2 - Call, 5
    // P3 - Fold
    // P4 - Raise, 10
    // P1 - Raise, 20
    // P2 - Call, 20

    addActionAndUpdateCurPlayer(ActionType::BET, 5);
    addActionAndUpdateCurPlayer(ActionType::CALL, 5);
    addActionAndUpdateCurPlayer(ActionType::FOLD, 0);
    addActionAndUpdateCurPlayer(ActionType::RAISE, 10);
    addActionAndUpdateCurPlayer(ActionType::RAISE, 20);
    addActionAndUpdateCurPlayer(ActionType::CALL, 20);

    // Now, expect current player to skip P3 since folded
    // Current player should be P4
    verifyCurPlayerAndUpdate("P4");
}

TEST_F(PositionTest, curPlayerUpdatesWithAllIns) {
    // Setup: FLOP, 4 players
    TestUtil::manualSetStreet(*gameData, Street::FLOP);
    playerManager->addNewPlayers(TestUtil::getSubset(playersInfo, 0, 4));
    positionManager->allocatePositions();
    positionManager->setEarlyPositionToAct();

    // Add the following actions:
    // P1 - Bet, 5
    // P2 - All In Bet, 200
    // P3 - Call, 200
    // P4 - Raise, 300
    // P1 - Fold, 0

    addActionAndUpdateCurPlayer(ActionType::BET, 5);
    addActionAndUpdateCurPlayer(ActionType::ALL_IN_BET, 200);
    addActionAndUpdateCurPlayer(ActionType::CALL, 200);
    addActionAndUpdateCurPlayer(ActionType::RAISE, 300);
    addActionAndUpdateCurPlayer(ActionType::FOLD, 0);

    // Now, expect current player to skip P2 since all-in
    // Current player should be P3
    verifyCurPlayerAndUpdate("P3");
}

TEST_F(PositionTest, RotatePositionResetsPlayerStatus) {
    // Setup: FLOP, 4 players
    playerSetup(4);

    // Fold Players 1, 2 and 4
    addActionAndUpdateCurPlayer(ActionType::FOLD, 0);
    addActionAndUpdateCurPlayer(ActionType::FOLD, 0);
    addActionAndUpdateCurPlayer(ActionType::BET, 5);
    addActionAndUpdateCurPlayer(ActionType::FOLD, 0);

    // Rotate positions for a new round
    positionManager->rotatePositions();
    positionManager->setEarlyPositionToAct();

    verifyCurPlayerAndUpdate("P4");
    verifyCurPlayerAndUpdate("P1");
    verifyCurPlayerAndUpdate("P2");
    verifyCurPlayerAndUpdate("P3");
    verifyCurPlayerAndUpdate("P4");
}