#include "../include/GameState/State.h"
#include "../include/GameState/StateManager.h"

void StreetEnd::enter() {
    cout << "State: Street End" << endl;
}

void StreetEnd::transition(StateManager& stateManager) {
    stateManager.setState(make_unique<Showdown>());
}