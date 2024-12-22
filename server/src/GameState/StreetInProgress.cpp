#include "../include/GameState/State.h"
#include "../include/GameState/StateManager.h"

void StreetInProgress::enter() {
    cout << "State: Street In Process" << endl;
}

void StreetInProgress::transition(StateManager& stateManager) {
    stateManager.setState(make_unique<StreetEnd>());
}