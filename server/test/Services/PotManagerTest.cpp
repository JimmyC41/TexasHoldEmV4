#include <gtest/gtest.h>
#include "../../include/Services/PlayerManager.h"
#include "../../include/Services/PotManager.h"
#include "../../include/Services/ActionManager.h"
#include "../../include/Utils/TestUtil.h"
#include "../../include/Utils/GameUtil.h"
#include "../../include/Utils/PrintUtil.h"

class PotTest : public::testing::Test {
protected:
    GameData gameData;
    PlayerManager playerManager;
    ActionManager actionManager;
    PotManager potManager;

    vector<pair<string, size_t>> playersInfo = 
    {
        {"P1", 100},
        {"P2", 200},
        {"P3", 300},
        {"P4", 400},
        {"P5", 500},
        {"P6", 400},
        {"P7", 300},
        {"P8", 200},
        {"P9", 100}
    };

    PotTest() : 
        playerManager(gameData), 
        actionManager(gameData),
        potManager(gameData) 
    {
            playerManager.addNewPlayers(TestUtil::getSubset(playersInfo, 0, 9));
    }

    // For each action, adds the action to timeline
    void parseActionTimeline(vector<tuple<string, ActionType, size_t>> actionTimeline) {
        for (auto& [id, action, amount] : actionTimeline) {
            actionManager.addNewAction(id, action, amount);
        }
    }

    // Verifies if the Action Manager evaluates pots and dead chips as expected
    void verifyPotCalculation(vector<pair<size_t, vector<string>>> expectedPots, size_t expectedDeadChips) {
        potManager.calculatePots();
        EXPECT_EQ(TestUtil::getPotsChipsAndNames(gameData), expectedPots);
        EXPECT_EQ(gameData.getDeadChips(), expectedDeadChips);
    }
};

TEST_F(PotTest, NoSidePot) {
    vector<tuple<string, ActionType, size_t>> betCalled = {
        {"P1", ActionType::BET, 5},
        {"P2", ActionType::CALL, 5},
        {"P3", ActionType::CALL, 5},
        {"P4", ActionType::CALL, 5},
        {"P5", ActionType::CALL, 5},
        {"P6", ActionType::CALL, 5},
        {"P7", ActionType::CALL, 5},
        {"P8", ActionType::CALL, 5},
        {"P9", ActionType::CALL, 5},
    };
    parseActionTimeline(betCalled);
    verifyPotCalculation(
    {
        {45, {"P1", "P2", "P3", "P4", "P5", "P6", "P7", "P8", "P9"}}
    }, 0);
};

TEST_F(PotTest, SingleSidePot) {
    vector<tuple<string, ActionType, size_t>> singleSidePot = {
        {"P1", ActionType::ALL_IN_BET, 100},
        {"P2", ActionType::ALL_IN_RAISE, 200},
        {"P3", ActionType::CALL, 200},
        {"P4", ActionType::CALL, 200},
        {"P5", ActionType::CALL, 200},
        {"P6", ActionType::CALL, 200},
        {"P7", ActionType::CALL, 200},
        {"P8", ActionType::ALL_IN_CALL, 200},
        {"P9", ActionType::ALL_IN_CALL, 100},
    };
    parseActionTimeline(singleSidePot);
    verifyPotCalculation(
    {
        {900, {"P1", "P2", "P3", "P4", "P5", "P6", "P7", "P8", "P9"}},
        {700, {"P2", "P3", "P4", "P5", "P6", "P7", "P8"}}
    }, 0);
};

TEST_F(PotTest, MultipleSidePots) {
    vector<tuple<string, ActionType, size_t>> multipleSidePots = {
        {"P1", ActionType::ALL_IN_BET, 100},
        {"P2", ActionType::ALL_IN_RAISE, 200},
        {"P3", ActionType::ALL_IN_RAISE, 300},
        {"P4", ActionType::ALL_IN_RAISE, 400},
        {"P5", ActionType::CALL, 400},
        {"P6", ActionType::ALL_IN_CALL, 400},
        {"P7", ActionType::ALL_IN_CALL, 300},
        {"P8", ActionType::ALL_IN_CALL, 200},
        {"P9", ActionType::ALL_IN_CALL, 100},
    };
    parseActionTimeline(multipleSidePots);
    verifyPotCalculation(
    {
        {900, {"P1", "P2", "P3", "P4", "P5", "P6", "P7", "P8", "P9"}},
        {700, {"P2", "P3", "P4", "P5", "P6", "P7", "P8"}},
        {500, {"P3", "P4", "P5", "P6", "P7"}},
        {300, {"P4", "P5", "P6"}}
    }, 0);
};

TEST_F(PotTest, DeadMoney) {
    vector<tuple<string, ActionType, size_t>> playersFoldAfterBet = {
        {"P1", ActionType::ALL_IN_BET, 100},
        {"P2", ActionType::ALL_IN_RAISE, 200},
        {"P3", ActionType::ALL_IN_RAISE, 300},
        {"P4", ActionType::ALL_IN_RAISE, 400},
        {"P5", ActionType::CALL, 400},
        {"P6", ActionType::FOLD, 0},
        {"P7", ActionType::FOLD, 0},
        {"P8", ActionType::FOLD, 0},
        {"P9", ActionType::FOLD, 0},
        {"P1", ActionType::FOLD, 0},
        {"P2", ActionType::FOLD, 0},
        {"P3", ActionType::FOLD, 0},
    };
    parseActionTimeline(playersFoldAfterBet);
    verifyPotCalculation(
    {
        {1400, {"P4", "P5"}},
    }, 0);
};