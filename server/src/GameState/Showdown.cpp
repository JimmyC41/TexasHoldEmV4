#include "../include/GameState/State.h"
#include "../include/GameState/StateManager.h"

void Showdown::enter() {
    cout << "State: Showdown" << endl;
}

void Showdown::transition(StateManager& stateManager) {
    stateManager.setState(make_unique<AnnounceWinner>());
}