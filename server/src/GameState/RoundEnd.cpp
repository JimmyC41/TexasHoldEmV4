#include "../include/GameState/State.h"
#include "../include/GameState/StateManager.h"

void RoundEnd::enter() {
    cout << "State: Round End" << endl;
}

void RoundEnd::transition(StateManager& stateManager) {
    stateManager.setState(make_unique<RoundSetup>());
}