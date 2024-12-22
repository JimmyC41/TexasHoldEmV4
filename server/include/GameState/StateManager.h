#ifndef STATE_MANAGER_H
#define STATE_MANAGER_H

#include <memory>
#include "State.h"
using namespace std;

class StateManager {
private:
    unique_ptr<State> curState;
public:
    explicit StateManager() {};

    void setState(unique_ptr<State> newState) {
        curState = std::move(newState);
        curState->enter();
    }

    void transitionState() {
        if (curState) curState->transition(*this);
    }
};

#endif