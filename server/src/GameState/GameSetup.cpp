#include "../include/GameState/State.h"
#include "../include/GameState/StateManager.h"

void GameSetup::enter() {
    cout << "State: Game Setup" << endl;
}

void GameSetup::transition(StateManager& stateManager) {
    stateManager.setState(make_unique<RoundSetup>());
}