#include "../../include/States/Winner.h"
#include "../../include/States/GameSetup.h"
#include "../../include/GameController.h"

void Winner::execute() {
    cout << "(+) State Manger: Winner State\n" << endl;

    // Evaluate hand strengths and award pots
    PrintUtil::printPots(gameData);

    controller.getHandRankManager().evaluateRankedIds();
    controller.getPotManager().awardPots();

    // Print the Game State
    controller.getIOManager().displayGameStateStdOut();

    // Rotate positions
    controller.getPositionManager().rotatePositions();

    // Go to Game Setup state
    transition();
}

void Winner::transition() {
    controller.getStateManager().setState(make_unique<GameSetup>(gameData, controller));
 }