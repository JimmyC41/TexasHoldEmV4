#ifndef STATE_H
#define STATE_H

#include "StateManager.h"
#include <string>
#include <iostream>

using namespace std;

class StateManager;

class State {
protected:
    GameData& gameData;
    GameController& controller;
    StateManager& stateManager;

    State(GameData& gd, GameController& ctrl, StateManager& sm)
        : gameData(gd), controller(ctrl), stateManager(sm) {}

public:
    virtual ~State() = default;
    virtual void execute() = 0;
    virtual void transition() = 0;
};

#endif