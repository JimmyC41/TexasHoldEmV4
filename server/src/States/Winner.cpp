#include "../../include/States/Winner.h"
#include "../../include/States/GameSetup.h"
#include "../../include/GameController.h"

void Winner::execute() {
    // cout << "--------------------------------------------------------------\n";
    // cout << "(+) State Manger: Winner State\n" << endl;

    // Evaluate hand strengths and award pots
    controller.getHandRankManager().evaluateRankedIds();
    controller.getPotManager().awardPots();

    // Event Manager: Publish PotWinner Event
    controller.getEventManager().publishPotUpdateEvent();
    controller.getEventManager().publishPotWinnerEvent();

    // Rotate positions
    controller.getPositionManager().rotatePositions();

    // Clear the board and publish the clean board state
    controller.getDealerManager().clearBoard();
    controller.getEventManager().publishDealBoardEvent();

    // Go to Game Setup state
    transition();
}

void Winner::transition() {
    controller.getStateManager().setState(make_unique<GameSetup>(gameData, controller));
 }