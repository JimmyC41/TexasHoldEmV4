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

bool GameController::handleJoinGameRequest(const string& name, const uint32_t& chips) {
    if (!rpcValidator.canJoin(name, chips)) return false;
    requestManager.addToPlayerJoinQueue(name, chips);
    return true;
}

bool GameController::handleLeaveGameRequest(const string& name) {
    if (!rpcValidator.canLeave(name)) return false;
    requestManager.addToPlayerLeaveQueue(name);
    return true;
}

bool GameController::handlePlayerActionRequest(const string& id, ActionType type, const uint32_t& amount) {
    if (!rpcValidator.isPossibleAction(id, type, amount)) return false;
    requestManager.addToActionQueue(type, amount);
    return true;
}

bool GameController::handleSubscribe(const string& id, grpc::ServerWriter<GameStreamRes>* writer) {
     if (!rpcValidator.isInGame(id)) return false;
     eventManager.addSubscriber(writer);
     return true;
}

void GameController::handleUnsubscribe(grpc::ServerWriter<GameStreamRes>* writer) {
    eventManager.removeSubscriber(writer);
}