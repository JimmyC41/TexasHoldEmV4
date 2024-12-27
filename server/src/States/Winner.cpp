#include "../../include/States/Winner.h"
#include "../../include/States/GameSetup.h"

void Winner::execute() {
    cout << "Executing Winner" << endl;
}

void Winner::transition() {
    stateManager.setState(make_unique<GameSetup>(gameData, controller, stateManager));
 }