#include "../include/GameController.h"

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
    eventManager(gameData) {}

void GameController::startGame() {
    stateManager.setState(make_unique<GameSetup>(gameData, *this));
}