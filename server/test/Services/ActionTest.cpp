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
        {"P9", 900}
    };

    ActionTest() : playerManager(gameData), positionManager(gameData), actionManager(gameData) {
        // Add players, allocate positions, set EP to act, sets players to be in hand
        playerManager.addNewPlayers(TestUtil::getSubset(playersInfo, 0, 9));
        positionManager.allocatePositions();
        positionManager.setEarlyPositionToAct();
    }

    void verifyGameData(
        GameData& gameData,
        vector<tuple<string, ActionType, size_t>> expectedTimeline,
        ActionType expectedActiveActionType) {

        auto actualTimeline = TestUtil::getActionTimelineVector(gameData);
        EXPECT_EQ(actualTimeline, expectedTimeline);

        auto actualActiveActionType = GameUtil::getActiveActionType(gameData);
        EXPECT_EQ(actualActiveActionType, expectedActiveActionType);
    }

    // Verifies the actionTimeline and the activeAction is correctly updated in the Game Data
    void verifyNewAction(
        ActionType newActionType,
        size_t amount,
        vector<tuple<string, ActionType, size_t>> allActions,
        int actionNum,
        ActionType expectedActiveAction) {
        
        actionManager.addNewAction(gameData.getCurPlayerId(), newActionType, amount);
        verifyGameData(gameData, TestUtil::getSubset(allActions, 0, actionNum), expectedActiveAction);
        positionManager.updatePlayerToAct();
    }
};

// Check if the Action Manager processes a new action and updates the internal GameData
TEST_F(ActionTest, NewActionAdded) {
    vector<tuple<string, ActionType, size_t>> expectedTimeline = {
        {"P1", ActionType::CHECK, 0},
        {"P2", ActionType::BET, 1},
        {"P3", ActionType::CALL, 1},
        {"P4", ActionType::RAISE, 2},
        {"P5", ActionType::CALL, 2},
        {"P6", ActionType::FOLD, 0},
        {"P7", ActionType::ALL_IN_BET, 700},
        {"P8", ActionType::CALL, 700},
        {"P9", ActionType::FOLD, 0},
        {"P1", ActionType::ALL_IN_CALL, 100},
    };

    verifyNewAction(ActionType::CHECK, 0, expectedTimeline, 1, ActionType::NONE);
    verifyNewAction(ActionType::BET, 1, expectedTimeline, 2, ActionType::BET);
    verifyNewAction(ActionType::CALL, 1, expectedTimeline, 3, ActionType::BET);
    verifyNewAction(ActionType::RAISE, 2, expectedTimeline, 4, ActionType::RAISE);
    verifyNewAction(ActionType::CALL, 2, expectedTimeline, 5, ActionType::RAISE);
    verifyNewAction(ActionType::FOLD, 0, expectedTimeline, 6, ActionType::RAISE);
    verifyNewAction(ActionType::ALL_IN_BET, 700, expectedTimeline, 7, ActionType::ALL_IN_BET);
    verifyNewAction(ActionType::CALL, 700, expectedTimeline, 8, ActionType::ALL_IN_BET);
    verifyNewAction(ActionType::FOLD, 0, expectedTimeline, 9, ActionType::ALL_IN_BET);
    verifyNewAction(ActionType::ALL_IN_CALL, 100, expectedTimeline, 10, ActionType::ALL_IN_BET);
};

// Verifies if the Action Manager generates the correct set of possible actions