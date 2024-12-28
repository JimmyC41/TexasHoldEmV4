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

    State(GameData& gd, GameController& ctrl) : gameData(gd), controller(ctrl) {}

public:
    virtual ~State() = default;
    virtual void execute() = 0;
    virtual void transition() = 0;
};

#endif