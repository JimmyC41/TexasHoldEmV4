#include <gtest/gtest.h>
#include "../../include/Services/DealerManager.h"
#include "../../include/Services/PlayerManager.h"
#include "../../include/Utils/TestUtil.h"
#include "../../include/Utils/GameUtil.h"
#include "../../include/Utils/PrintUtil.h"

class PlayerTest : public ::testing::Test {
protected:
    PlayerManager playerManager;
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

    PlayerTest() : playerManager(gameData) {}

    void TearDown() override {
        playerManager.removeAllPlayers();
    }
};

TEST_F(PlayerTest, AddSinglePlayers) {
    playerManager.addNewPlayers(TestUtil::getSubset(playersInfo, 0, 1));
    EXPECT_EQ(playerManager.getNumPlayers(), 1);
    PrintUtil::printPlayers(gameData);

    playerManager.addNewPlayers(TestUtil::getSubset(playersInfo, 1, 2));
    EXPECT_EQ(playerManager.getNumPlayers(), 2);
    PrintUtil::printPlayers(gameData);

    playerManager.addNewPlayers(TestUtil::getSubset(playersInfo, 2, 3));
    EXPECT_EQ(playerManager.getNumPlayers(), 3);
    PrintUtil::printPlayers(gameData);
}

TEST_F(PlayerTest, AddMultiplePlayers) {
    playerManager.addNewPlayers(TestUtil::getSubset(playersInfo, 0, 9));
    EXPECT_EQ(playerManager.getNumPlayers(), 9);
    PrintUtil::printPlayers(gameData);
}

TEST_F(PlayerTest, RemoveSinglePlayers) {
    playerManager.addNewPlayers(TestUtil::getSubset(playersInfo, 0, 1));
    EXPECT_EQ(playerManager.getNumPlayers(), 1);
    PrintUtil::printPlayers(gameData);

    playerManager.removeExistingPlayers({"P1"});
    EXPECT_EQ(playerManager.getNumPlayers(), 0);
    PrintUtil::printPlayers(gameData);

    playerManager.addNewPlayers(TestUtil::getSubset(playersInfo, 1, 2));
    EXPECT_EQ(playerManager.getNumPlayers(), 1);
    PrintUtil::printPlayers(gameData);

    playerManager.removeExistingPlayers({"P2"});
    EXPECT_EQ(playerManager.getNumPlayers(), 0);
    PrintUtil::printPlayers(gameData);
}

TEST_F(PlayerTest, RemoveMultiplePlayers) {
    playerManager.addNewPlayers(TestUtil::getSubset(playersInfo, 0, 9));
    EXPECT_EQ(playerManager.getNumPlayers(), 9);
    PrintUtil::printPlayers(gameData);

    playerManager.removeExistingPlayers({"P1", "P3", "P5", "P7", "P9"});
    EXPECT_EQ(playerManager.getNumPlayers(), 4);
    PrintUtil::printPlayers(gameData);

    playerManager.removeExistingPlayers({"P2", "P4", "P6"});
    EXPECT_EQ(playerManager.getNumPlayers(), 1);
    PrintUtil::printPlayers(gameData);
}