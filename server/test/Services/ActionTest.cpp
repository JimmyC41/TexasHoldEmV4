#include <gtest/gtest.h>
#include "../../include/Services/PlayerManager.h"
#include "../../include/Services/PositionManager.h"
#include "../../include/Services/ActionManager.h"
#include "../../include/Utils/TestUtil.h"
#include "../../include/Utils/GameUtil.h"
#include "../../include/Utils/PrintUtil.h"

class ActionTest : public::testing::Test {
protected:
    GameData gameData;
    PlayerManager playerManager;
    PositionManager positionManager;
    ActionManager actionManager;

    vector<pair<string, uint32_t>> playersInfo = 
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

    vector<tuple<string, ActionType, uint32_t>> limpedPreflop = {
        {"P1", ActionType::POST_SMALL, 5},
        {"P2", ActionType::POST_BIG, 10},
        {"P3", ActionType::CALL, 10},
        {"P4", ActionType::CALL, 10},
        {"P5", ActionType::CALL, 10},
        {"P6", ActionType::CALL, 10},
        {"P7", ActionType::CALL, 10},
        {"P8", ActionType::CALL, 10},
        {"P9", ActionType::CALL, 10},
        {"P1", ActionType::CALL, 10},
        {"P2", ActionType::CHECK, 0},
    };

    ActionTest() : playerManager(gameData), positionManager(gameData), actionManager(gameData) {
        // Add players, allocate positions, set EP to act, sets players to be in hand
        TestUtil::manualSetStreet(gameData, Street::FLOP);
        playerManager.addNewPlayers(TestUtil::getSubset(playersInfo, 0, 9));
        positionManager.allocatePositions();
        positionManager.setEarlyPositionToAct();
    }

    void TearDown() override {
        TestUtil::manualClearActionTimeline(gameData);
    }

    void verifyGameData(
        GameData& gameData,
        vector<tuple<string, ActionType, uint32_t>> expectedTimeline,
        ActionType expectedActiveActionType) {

        auto actualTimeline = TestUtil::getActionTimelineVector(gameData);
        EXPECT_EQ(actualTimeline, expectedTimeline);

        auto actualActiveActionType = GameUtil::getActiveActionType(gameData);
        EXPECT_EQ(actualActiveActionType, expectedActiveActionType);
    }

    // Verifies the actionTimeline and the activeAction is correctly updated in the Game Data
    void verifyNewAction(
        ActionType newActionType,
        uint32_t amount,
        vector<tuple<string, ActionType, uint32_t>> expectedTimeline,
        ActionType expectedActive) {
        
        actionManager.addNewAction(gameData.getCurPlayer()->getId(), newActionType, amount);
        verifyGameData(gameData, expectedTimeline, expectedActive);
        positionManager.updatePlayerToAct();
    }

    // Verifies the possible actions generated by the Action Manager in the Game Data is as expected
    // Called AFTER adding a new action
    void verifyPossibleActions(vector<tuple<ActionType, PossibleAmounts>> expected) {
        actionManager.generatePossibleActionsForCurPlayer();
        auto actual = TestUtil::getPossibleActionsVector(gameData);

        EXPECT_EQ(expected, actual);
    }

    // Adds the small and big blind action to the timeline
    void verifyPostingBlinds() {
        verifyNewAction(ActionType::POST_SMALL, 5,
            TestUtil::getSubset(limpedPreflop, 0, 1), ActionType::POST_SMALL);
    
        verifyNewAction(ActionType::POST_BIG, 10,
            TestUtil::getSubset(limpedPreflop, 0, 2), ActionType::POST_BIG);
    }
};

// Check if the Action Manager processes a new action and updates the internal GameData
TEST_F(ActionTest, NewActionAdded) {
    vector<tuple<string, ActionType, uint32_t>> actions = {
        {"P1", ActionType::CHECK, 0},
        {"P2", ActionType::BET, 50},
        {"P3", ActionType::CALL, 50},
        {"P4", ActionType::RAISE, 200},
        {"P5", ActionType::CALL, 200},
        {"P6", ActionType::FOLD, 0},
        {"P7", ActionType::ALL_IN_BET, 300},
        {"P8", ActionType::ALL_IN_CALL, 200},
        {"P9", ActionType::FOLD, 0}
    };

    verifyNewAction(ActionType::CHECK, 0, 
        TestUtil::getSubset(actions, 0, 1), ActionType::NONE);

    verifyNewAction(ActionType::BET, 50, 
        TestUtil::getSubset(actions, 0, 2), ActionType::BET);

    verifyNewAction(ActionType::CALL, 50, 
        TestUtil::getSubset(actions, 0, 3), ActionType::BET);

    verifyNewAction(ActionType::RAISE, 200,
        TestUtil::getSubset(actions, 0, 4), ActionType::RAISE);

    verifyNewAction(ActionType::CALL, 200, 
        TestUtil::getSubset(actions, 0, 5), ActionType::RAISE);

    verifyNewAction(ActionType::FOLD, 0, 
        TestUtil::getSubset(actions, 0, 6), ActionType::RAISE);

    verifyNewAction(ActionType::ALL_IN_BET, 300, 
        TestUtil::getSubset(actions, 0, 7), ActionType::ALL_IN_BET);

    verifyNewAction(ActionType::ALL_IN_CALL, 200, 
        TestUtil::getSubset(actions, 0, 8), ActionType::ALL_IN_BET);

    verifyNewAction(ActionType::FOLD, 0, 
        TestUtil::getSubset(actions, 0, 9), ActionType::ALL_IN_BET);
};

// Verifies if the Action Manager generates the correct set of possible actions
// provided the action timeline. For each player, we verify the vector of
// possible actions generated by the action manager, then add one of those 
// actions to generate the possible actions for the next player.

TEST_F(ActionTest, PossibleActions) {
    vector<tuple<string, ActionType, uint32_t>> actions = {
        {"P1", ActionType::CHECK, 0},
        {"P2", ActionType::BET, 50},
        {"P3", ActionType::RAISE, 100},
        {"P4", ActionType::FOLD, 0},
        {"P5", ActionType::RAISE, 300},
        {"P6", ActionType::ALL_IN_RAISE, 400},
        {"P7", ActionType::ALL_IN_CALL, 300},
        {"P8", ActionType::ALL_IN_CALL, 200},
        {"P9", ActionType::FOLD, 0}
    };

    // P1 is the first to act - can check, bet or fold
    // Suppose P1 checks
    vector<tuple<ActionType, PossibleAmounts>> expected = {
        {ActionType::CHECK, monostate{}},
        {ActionType::BET, make_tuple(0, 100)},
        {ActionType::ALL_IN_BET, uint32_t{100}},
        {ActionType::FOLD, monostate{}}
    };
    verifyPossibleActions(expected);
    verifyNewAction(ActionType::CHECK, 0,
        TestUtil::getSubset(actions, 0, 1), ActionType::NONE);
    
    // P2 is the next to act - can check, bet or fold
    // Suppose P2 bets 50
    expected = {
        {ActionType::CHECK, monostate{}},
        {ActionType::BET, make_tuple(0, 200)},
        {ActionType::ALL_IN_BET, uint32_t{200}},
        {ActionType::FOLD, monostate{}}
    };
    verifyPossibleActions(expected);
    verifyNewAction(ActionType::BET, 50,
        TestUtil::getSubset(actions, 0, 2), ActionType::BET);
    
    // P3 is the next to act - can call, raise or fold
    // Suppose P3 raises to 100
    expected = {
        {ActionType::CALL, uint32_t{50}},
        {ActionType::RAISE, make_tuple(100, 300)},
        {ActionType::ALL_IN_RAISE, uint32_t{300}},
        {ActionType::FOLD, monostate{}}
    };
    verifyPossibleActions(expected);
    verifyNewAction(ActionType::RAISE, 100,
        TestUtil::getSubset(actions, 0, 3), ActionType::RAISE);
    
    // P4 - is the next to act - can call, raise or fold
    // Suppose P4 folds
    expected = {
        {ActionType::CALL, uint32_t{100}},
        {ActionType::RAISE, make_tuple(200, 400)},
        {ActionType::ALL_IN_RAISE, uint32_t{400}},
        {ActionType::FOLD, monostate{}}
    };
    verifyPossibleActions(expected);
    verifyNewAction(ActionType::FOLD, 0,
        TestUtil::getSubset(actions, 0, 4), ActionType::RAISE);

    // P5 is the next to act - can call, raise or fold
    // Suppose P5 raises to 300
    expected = {
        {ActionType::CALL, uint32_t{100}},
        {ActionType::RAISE, make_tuple(200, 400)},
        {ActionType::FOLD, monostate{}}
    };
    verifyPossibleActions(expected);
    verifyNewAction(ActionType::RAISE, 300,
        TestUtil::getSubset(actions, 0, 5), ActionType::RAISE);

    // P6 is the next to act - can call, raise all-in or fold
    // Suppose P6 raises all-in to 400
    expected = {
        {ActionType::CALL, uint32_t{300}},
        {ActionType::ALL_IN_RAISE, uint32_t{400}},
        {ActionType::FOLD, monostate{}}
    };
    verifyPossibleActions(expected);
    verifyNewAction(ActionType::ALL_IN_RAISE, 400,
        TestUtil::getSubset(actions, 0, 6), ActionType::ALL_IN_RAISE);
    
    // P7 is the next to act - can call all-in or fold
    // Suppose P7 calls all-in
    expected = {
        {ActionType::ALL_IN_CALL, uint32_t{300}},
        {ActionType::FOLD, monostate{}}
    };
    verifyPossibleActions(expected);
    verifyNewAction(ActionType::ALL_IN_CALL, 300,
        TestUtil::getSubset(actions, 0, 7), ActionType::ALL_IN_RAISE);
    
    // P8 is the next to act - can call all-in or fold
    // Suppose P8 calls all-in
    expected = {
        {ActionType::ALL_IN_CALL, uint32_t{200}},
        {ActionType::FOLD, monostate{}}
    };
    verifyPossibleActions(expected);
    verifyNewAction(ActionType::ALL_IN_CALL, 200,
        TestUtil::getSubset(actions, 0, 8), ActionType::ALL_IN_RAISE);
    
    // P9 is the next to act - can call all-in or fold
    // Suppose P9 folds
    expected = {
        {ActionType::ALL_IN_CALL, uint32_t{100}},
        {ActionType::FOLD, monostate{}}
    };
    verifyPossibleActions(expected);
    verifyNewAction(ActionType::FOLD, 0,
        TestUtil::getSubset(actions, 0, 9), ActionType::ALL_IN_RAISE);
};

TEST_F(ActionTest, PossibleActionsForLimpedBigBlind) {
    PrintUtil::printPlayers(gameData);

    // Add small and big blind actions
    verifyPostingBlinds(); 

    // All players call the BB
    for (int i = 3; i <= 10; i++) {
        verifyNewAction(ActionType::CALL, 10,
            TestUtil::getSubset(limpedPreflop, 0, i), ActionType::POST_BIG);
    }
    
    // BB should have options: check (not call), raise, fold
    vector<tuple<ActionType, PossibleAmounts>> expected = {
        {ActionType::CHECK, monostate{}},
        {ActionType::RAISE, make_tuple(20, 200)},
        {ActionType::ALL_IN_RAISE, uint32_t{200}},
        {ActionType::FOLD, monostate{}}
    };
    verifyPossibleActions(expected);
};

TEST_F(ActionTest, ActionsFinishedAllPlayersCheck) {
    // All players check their option
    vector<tuple<string, ActionType, uint32_t>> actions = {
        {"P1", ActionType::CHECK, 0},
        {"P2", ActionType::CHECK, 0},
        {"P3", ActionType::CHECK, 0},
        {"P4", ActionType::CHECK, 0},
        {"P5", ActionType::CHECK, 0},
        {"P6", ActionType::CHECK, 0},
        {"P7", ActionType::CHECK, 0},
        {"P8", ActionType::CHECK, 0},
        {"P9", ActionType::CHECK, 0}
    };
    for (int i = 1; i < 10; i++) {
        EXPECT_EQ(actionManager.isActionsFinished(), false);
        verifyNewAction(ActionType::CHECK, 0,
        TestUtil::getSubset(actions, 0, i), ActionType::NONE);
    }
    
    // All 9 players have checked their option - action is over!
    EXPECT_EQ(actionManager.isActionsFinished(), true);

    // Move to next street, reset checks - action is not over!
    EXPECT_EQ(actionManager.isActionsFinished(), false);
}

TEST_F(ActionTest, ActionsFinishedAfterPlayersLimpBigBlind) {
    // Add small and big blind actions
    verifyPostingBlinds(); 

    // All players call the BB - check actions are NOT finished yet
    // until the BB checks ther option!
    for (int i = 3; i <= 10; i++) {
        EXPECT_EQ(actionManager.isActionsFinished(), false);
        verifyNewAction(ActionType::CALL, 10,
        TestUtil::getSubset(limpedPreflop, 0, i), ActionType::POST_BIG);
    }

    // BB (player checks their option) - actions are now finished!
    verifyNewAction(ActionType::CHECK, 0,
        TestUtil::getSubset(limpedPreflop, 0, 11), ActionType::POST_BIG);
    EXPECT_EQ(actionManager.isActionsFinished(), true);
}