#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include "Shared/GameData.h"
#include "States/StateManager.h"
#include "Services/ActionManager.h"
#include "Services/DealerManager.h"
#include "Services/HandRankManager.h"
#include "Services/PlayerManager.h"
#include "Services/PositionManager.h"
#include "Services/PotManager.h"
#include "Services/IOManager.h"
#include "States/State.h"
#include "States/GameSetup.h"
#include "States/BettingStreet.h"
#include "States/Winner.h"
#include <memory>

class GameController {
private:
    GameData gameData;
    ActionManager actionManager;
    DealerManager dealerManager;
    HandRankManager handRankManager;
    PlayerManager playerManager;
    PositionManager positionManager;
    PotManager potManager;
    IOManager inputOutputManager;
    StateManager stateManager;

public:
    GameController();
    void beginGameSetup();
    void moveToNextState();

    ActionManager& getActionManager() { return actionManager; }
    DealerManager& getDealerManager() { return dealerManager; }
    HandRankManager& getHandRankManager() { return handRankManager; }
    PlayerManager& getPlayerManager() { return playerManager; }
    PositionManager& getPositionManager() { return positionManager; }
    PotManager& getPotManager() { return potManager; }
    IOManager& getIOManager() { return inputOutputManager; }
};

#endif