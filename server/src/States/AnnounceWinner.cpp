#include "../include/State.h"
#include "../include/StateManager.h"

void AnnounceWinner::enter() {
    cout << "State: Announce Winner" << endl;
}

void AnnounceWinner::transition(StateManager& stateManager) {
    stateManager.setState(make_unique<RoundEnd>());
}