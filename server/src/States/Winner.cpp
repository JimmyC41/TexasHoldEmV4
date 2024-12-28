#include "../../include/States/Winner.h"
#include "../../include/States/GameSetup.h"
#include "../../include/GameController.h"

void Winner::execute() {
    cout << "(State Manger) New State: Winner" << endl;
}

void Winner::transition() {
    controller.getStateManager().setState(make_unique<GameSetup>(gameData, controller));
 }