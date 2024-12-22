#include "../include/State.h"
#include "../include/StateManager.h"

void StreetInProgress::enter() {
    cout << "State: Street In Process" << endl;
}

void StreetInProgress::transition(StateManager& stateManager) {
    stateManager.setState(make_unique<StreetEnd>());
}