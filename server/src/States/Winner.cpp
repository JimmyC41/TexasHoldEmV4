#include "../../include/States/Winner.h"
#include "../../include/States/GameSetup.h"
#include "../../include/GameController.h"

void Winner::execute() {
    // cout << "--------------------------------------------------------------\n";
    // cout << "(+) State Manger: Winner State\n" << endl;

    // Evaluate hand rankings and award pots to the winner
    // Then, publish the pot winner and clear pots
    controller.getHandRankManager().evaluateRankedIds();
    controller.getPotManager().awardPots();
    controller.getEventManager().publishPotUpdateEvent();
    controller.getEventManager().publishPotWinnerEvent();
    controller.getEventManager().publishPlayersUpdateEvent();

    // CLEAR GAME STATE FOR THE NEXT RD

    // Clear player hands
    controller.getDealerManager().clearPlayerHands();
    controller.getEventManager().publishDealPlayersEvent();

    // Clear the board
    controller.getDealerManager().clearBoard();
    controller.getEventManager().publishDealBoardEvent();

    // Clear the last action
    controller.getActionManager().clearActiveAction();
    controller.getEventManager().publishNewPlayerActionEvent();

    // Rotate positions and go to the game setup state
    controller.getPositionManager().rotatePositions();

    cout << "TRANSITIONING TO GAME SETUP!" << endl;
    transition();
}

void Winner::transition() {
    controller.getStateManager().setState(make_unique<GameSetup>(gameData, controller));
 }