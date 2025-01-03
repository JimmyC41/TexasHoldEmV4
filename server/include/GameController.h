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
#include "Services/EventManager.h"
#include "Services/RequestManager.h"
#include "Services/RPCValidator.h"
#include "States/State.h"
#include "States/GameSetup.h"
#include "States/BettingStreet.h"
#include "States/Winner.h"
#include "texas_holdem.grpc.pb.h"

#include <memory>
#include <mutex>

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
    EventManager eventManager;
    RequestManager requestManager;
    RPCValidator rpcValidator;

public:
    GameController();
    void startGame();

    ActionManager& getActionManager() { return actionManager; }
    DealerManager& getDealerManager() { return dealerManager; }
    HandRankManager& getHandRankManager() { return handRankManager; }
    PlayerManager& getPlayerManager() { return playerManager; }
    PositionManager& getPositionManager() { return positionManager; }
    PotManager& getPotManager() { return potManager; }
    IOManager& getIOManager() { return inputOutputManager; }
    StateManager& getStateManager() { return stateManager; }
    EventManager& getEventManager() { return eventManager; }
    GameData& getGameData() { return gameData; }
    RequestManager& getRequestManager() { return requestManager; }

    // State Transition Methods
    bool isAtLeastTwoPlayers() { return GameUtil::getNumPlayers(gameData) > 1; }
    bool isShortPlayersInHand() { return GameUtil::isShortPlayersInHand(gameData); }
    bool isBettingStreetComplete() { return actionManager.isActionsFinished(); }

    // gRPC Handling Methods
    bool handleJoinGameRequest(const string& name, const uint32_t& chips);
    bool handleLeaveGameRequest(const string& name);
    bool handlePlayerActionRequest(const string& id, ActionType type, const uint32_t& amount = 0);
    bool handleSubscribe(const string& id, grpc::ServerWriter<GameStreamRes>* writer);
    void handleUnsubscribe(grpc::ServerWriter<GameStreamRes>* writer);
};

#endif