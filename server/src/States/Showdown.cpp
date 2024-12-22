#include "../include/State.h"
#include "../include/StateManager.h"

void Showdown::enter() {
    cout << "State: Showdown" << endl;
}

void Showdown::transition(StateManager& stateManager) {
    stateManager.setState(make_unique<AnnounceWinner>());
}