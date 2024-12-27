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
    stateManager(gameData, *this) {}

void GameController::beginGameSetup() {
    stateManager.setState(make_unique<GameSetup>(gameData, *this, stateManager));
}

void GameController::moveToNextState() {
    stateManager.transitionState();
}