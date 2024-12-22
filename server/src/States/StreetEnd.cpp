#include "../include/State.h"
#include "../include/StateManager.h"

void StreetEnd::enter() {
    cout << "State: Street End" << endl;
}

void StreetEnd::transition(StateManager& stateManager) {
    stateManager.setState(make_unique<Showdown>());
}