#include <gtest/gtest.h>
#include "../../include/Services/PlayerManager.h"
#include "../../include/Services/PositionManager.h"
#include "../../include/Services/PotManager.h"
#include "../../include/Services/ActionManager.h"
#include "../../include/Services/HandRankManager.h"
#include "../../include/Services/DealerManager.h"
#include "../../include/Services/IOManager.h"
#include "../../include/Utils/TestUtil.h"
#include "../../include/Utils/GameUtil.h"
#include "../../include/Utils/PrintUtil.h"
#include "../../include/Entities/PossibleAction.h"
#include "../../include/Entities/PossibleActions/PossibleAllInBet.h"
#include "../../include/Entities/PossibleActions/PossibleAllInCall.h"
#include "../../include/Entities/PossibleActions/PossibleAllInRaise.h"
#include "../../include/Entities/PossibleActions/PossibleBet.h"
#include "../../include/Entities/PossibleActions/PossibleCall.h"
#include "../../include/Entities/PossibleActions/PossibleCheck.h"
#include "../../include/Entities/PossibleActions/PossibleFold.h"
#include "../../include/Entities/PossibleActions/PossibleRaise.h"

class IOTest : public::testing::Test {
protected:
    GameData gameData;
    PlayerManager playerManager;
    ActionManager actionManager;
    PotManager potManager;
    HandRankManager handRankManager;
    DealerManager dealer;
    PositionManager positionManager;
    IOManager ioManager;


    IOTest() : 
        playerManager(gameData), 
        actionManager(gameData),
        potManager(gameData),
        handRankManager(gameData),
        dealer(gameData),
        positionManager(gameData),
        ioManager(gameData) {}

    void TearDown() override {
        playerManager.removeAllPlayers();
        gameData.setBigBlind(2);
    }
};

TEST_F(IOTest, addPlayersStdIn) {
    auto newPlayers = ioManager.addPlayersStdIn();
    playerManager.addNewPlayers(newPlayers);
    PrintUtil::printPlayers(gameData);
};

TEST_F(IOTest, removePlayersStdIn) {
    // First, add players to the game
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
    TestUtil::manualAddPlayers(gameData, playerManager, positionManager, playersInfo);

    // Then, attempt player removal
    auto playersToRemove = ioManager.removePlayersStdIn();
    playerManager.removeExistingPlayers(playersToRemove);
    positionManager.allocatePositions();
    PrintUtil::printPlayers(gameData);
};

TEST_F(IOTest, getAction) {
    // First, create a vector of possible actions
    // and manually push this to Game Data
    vector<shared_ptr<PossibleAction>> possible = {
        make_shared<PossibleAllInBet>(100),
        make_shared<PossibleAllInCall>(100),
        make_shared<PossibleAllInRaise>(100),
        make_shared<PossibleBet>(100),
        make_shared<PossibleCall>(100),
        make_shared<PossibleCheck>(),
        make_shared<PossibleFold>(),
        make_shared<PossibleRaise>(2, 100)
    };
    TestUtil::manualSetPossibleAction(gameData, possible);

    // Then, attempt to fetch action from console
    ioManager.displayPossibleActionsStdOut();
    auto action = ioManager.getPlayerActionStdIn();
    PrintUtil::printClientAction(action);
};

