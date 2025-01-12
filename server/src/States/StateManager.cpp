#include "../../include/States/StateManager.h"
#include "../../include/States/State.h"

StateManager::StateManager(GameData& gd, GameController& ctrl) :
    gameData(gd),
    controller(ctrl),
    currentState() {}

void StateManager::setState(unique_ptr<State> newState) {
    currentState = std::move(newState);
    currentState->execute();
}

void StateManager::transitionState() {
    currentState->transition();
}