#ifndef STATE_MANAGER_H
#define STATE_MANAGER_H

class GameController;
class GameData;
class State;

#include <memory>
using namespace std;

class StateManager {
private:
    unique_ptr<State> currentState;
    GameData& gameData;
    GameController& controller;

public:
    StateManager(GameData& gd, GameController& ctrl);

    void setState(unique_ptr<State> newState);
    void transitionState();
};

#endif