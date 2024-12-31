#include <gtest/gtest.h>
#include "../../include/Services/DealerManager.h"
#include "../../include/Services/PlayerManager.h"
#include "../../include/Services/PositionManager.h"
#include "../../include/Utils/TestUtil.h"
#include "../../include/Utils/GameUtil.h"
#include "../../include/Utils/PrintUtil.h"

class PlayerTest : public ::testing::Test {
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

    PlayerTest() : playerManager(gameData), positionManager(gameData) {}


    // Add new players, allocate positions and sort, then print players to the console
    void addPlayersAndAllocatePositions(vector<pair<string, size_t>> playersInfo, int expectedNumPlayers) {
        playerManager.addNewPlayers(playersInfo);
        positionManager.allocatePositions();
        EXPECT_EQ(playerManager.getNumPlayers(), expectedNumPlayers);
        // PrintUtil::printPlayers(gameData);
    }

    // Removes players, then prints players to the console
    void removePlayers(vector<string> players, int expectedNumPlayers) {
        playerManager.removeExistingPlayers(players);
        positionManager.allocatePositions();
        EXPECT_EQ(playerManager.getNumPlayers(), expectedNumPlayers);
        // PrintUtil::printPlayers(gameData);
    }

    void TearDown() override {
        playerManager.removeAllPlayers();
    }   
};

TEST_F(PlayerTest, AddSinglePlayers) {
    addPlayersAndAllocatePositions(TestUtil::getSubset(playersInfo, 0, 1), 1);
    addPlayersAndAllocatePositions(TestUtil::getSubset(playersInfo, 1, 2), 2);
    addPlayersAndAllocatePositions(TestUtil::getSubset(playersInfo, 2, 3), 3);
}

TEST_F(PlayerTest, AddMultiplePlayers) {
    addPlayersAndAllocatePositions(TestUtil::getSubset(playersInfo, 0, 9), 9);
}

TEST_F(PlayerTest, RemoveSinglePlayers) {
    addPlayersAndAllocatePositions(TestUtil::getSubset(playersInfo, 0, 1), 1);
    removePlayers({"P1"}, 0);
    addPlayersAndAllocatePositions(TestUtil::getSubset(playersInfo, 1, 2), 1);
    removePlayers({"P2"}, 0);
}

TEST_F(PlayerTest, RemoveMultiplePlayers) {
    addPlayersAndAllocatePositions(TestUtil::getSubset(playersInfo, 0, 9), 9);
    removePlayers({"P1", "P3", "P5", "P7", "P9"}, 4);
    removePlayers({"P2", "P4", "P6"}, 1);
}