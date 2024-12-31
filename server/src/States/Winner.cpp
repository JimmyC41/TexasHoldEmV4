#include "../../include/States/Winner.h"
#include "../../include/States/GameSetup.h"
#include "../../include/GameController.h"

void Winner::execute() {
    cout << "--------------------------------------------------------------\n";
    cout << "(+) State Manger: Winner State\n" << endl;

    PrintUtil::printPlayers(gameData);

    // Evaluate hand strengths and award pots
    PrintUtil::printPots(gameData);

    controller.getHandRankManager().evaluateRankedIds();
    controller.getPotManager().awardPots();

    // Rotate positions
    controller.getPositionManager().rotatePositions();

    PrintUtil::printPlayers(gameData);

    // Go to Game Setup state
    transition();
}

void Winner::transition() {
    controller.getStateManager().setState(make_unique<GameSetup>(gameData, controller));
 }