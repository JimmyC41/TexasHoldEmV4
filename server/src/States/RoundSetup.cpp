#include "../include/State.h"
#include "../include/StateManager.h"

void RoundSetup::enter() {
    cout << "State: Round Setup" << endl;
}

void RoundSetup::transition(StateManager& stateManager) {
    stateManager.setState(make_unique<StreetSetup>());
}