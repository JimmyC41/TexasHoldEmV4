#include "../include/GameController.h"

GameController::GameController() : stateManager() {}

void GameController::startGame() {
    cout << "Starting the game!" << endl;
    stateManager.setState(make_unique<GameSetup>());
}

void GameController::nextState() {
    stateManager.transitionState();
}

void GameController::runGame() {
    startGame();
    int i { 0 };
    while (i < 100) {
        nextState();
        i++;
    }
}