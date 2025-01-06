#include "../include/GameController.h"

constexpr int MAX_NUM_PLAYERS = 9;

GameController::GameController() :
    gameData(),
    actionManager(gameData),
    dealerManager(gameData),
    handRankManager(gameData),
    playerManager(gameData),
    positionManager(gameData),
    potManager(gameData),
    inputOutputManager(gameData),
    stateManager(gameData, *this),
    eventManager(gameData),
    requestManager(),
    rpcValidator(gameData) {}

void GameController::startGame() {
    stateManager.setState(make_unique<GameSetup>(gameData, *this));
}

pair<bool, string> GameController::handleJoinGameRequest(const string& name, const uint32_t& chips) {
    if (!rpcValidator.canJoin(name, chips)) {
        return pair<bool, string>(false, "JoinGameRequestRejected");
    }
    string id = requestManager.addToPlayerJoinQueue(name, chips);
    return pair<bool, string>(true, id);
}

pair<bool, string> GameController::handleLeaveGameRequest(const string& id) {
    if (!rpcValidator.canLeave(id)) {
        return pair<bool, string>(false, "LeaveGameRequestRejected");
    }
    requestManager.addToPlayerLeaveQueue(id);
    return pair<bool, string>(true, id);
}

pair<bool, string> GameController::handlePlayerActionRequest(const string& id, ActionType type, const uint32_t& amount) {
    if (!rpcValidator.isPossibleAction(id, type, amount)) {
        return pair<bool, string>(false, "PlayerActionRequestRejected");
    }
    requestManager.addToActionQueue(type, amount);
    return pair<bool, string>(true, id);
}

bool GameController::handleSubscribe(const string& id, grpc::ServerWriter<GameStreamRes>* writer) {
     if (!rpcValidator.isInGame(id)) return false;
     eventManager.addSubscriber(writer);
     return true;
}

void GameController::handleUnsubscribe(grpc::ServerWriter<GameStreamRes>* writer) {
    eventManager.removeSubscriber(writer);
}