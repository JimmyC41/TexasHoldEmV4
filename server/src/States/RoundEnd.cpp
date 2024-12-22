#include "../include/State.h"
#include "../include/StateManager.h"

void RoundEnd::enter() {
    cout << "State: Round End" << endl;
}

void RoundEnd::transition(StateManager& stateManager) {
    stateManager.setState(make_unique<RoundSetup>());
}