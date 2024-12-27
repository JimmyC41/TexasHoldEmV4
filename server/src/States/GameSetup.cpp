#include "../../include/States/GameSetup.h"
#include "../../include/States/BettingStreet.h"

void GameSetup::execute() {
    cout << "Executing Game Setup" << endl;
}

void GameSetup::transition() {
    stateManager.setState(make_unique<BettingStreet>(gameData, controller, stateManager));
 }