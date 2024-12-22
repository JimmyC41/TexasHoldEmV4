#include "../include/GameState/State.h"
#include "../include/GameState/StateManager.h"

void StreetSetup::enter() {
    cout << "State: Street Setup" << endl;
}

void StreetSetup::transition(StateManager& stateManager) {
    stateManager.setState(make_unique<StreetInProgress>());
}