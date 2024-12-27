#include "../../include/States/BettingStreet.h"
#include "../../include/States/Winner.h"

void BettingStreet::execute() {
    cout << "Executing Betting Street" << endl;
}

void BettingStreet::transition() {
    stateManager.setState(make_unique<Winner>(gameData, controller, stateManager));
 }