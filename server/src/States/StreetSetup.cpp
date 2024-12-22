#include "../include/State.h"
#include "../include/StateManager.h"

void StreetSetup::enter() {
    cout << "State: Street Setup" << endl;
}

void StreetSetup::transition(StateManager& stateManager) {
    stateManager.setState(make_unique<StreetInProgress>());
}