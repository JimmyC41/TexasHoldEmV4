#include "../include/GameState/State.h"
#include "../include/GameState/StateManager.h"

void RoundSetup::enter() {
    cout << "State: Round Setup" << endl;
}

void RoundSetup::transition(StateManager& stateManager) {
    stateManager.setState(make_unique<StreetSetup>());
}