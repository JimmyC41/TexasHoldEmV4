#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include "GameState/StateManager.h"
#include <memory>

class GameController {
private:
    StateManager stateManager;
public:
    GameController();
    void startGame();
    void nextState();
    void runGame();
};

#endif