#include "../../include/States/BettingStreet.h"
#include "../../include/States/Winner.h"
#include "../../include/GameController.h"

void BettingStreet::execute() {
    for (int street = static_cast<int>(Street::PRE_FLOP);
            street <= static_cast<int>(Street::RIVER); ++street)
    {
        gameData.setCurStreet(static_cast<Street>(street));
        executeStreet();

        // Early exit condition if less than 2 players in hand
        // Occurs when all but one players fold to a blind/bet
        // Skip betting street and go to the winner state
        if (controller.getActionManager().isShortPlayersInHand()) {
            transition();
            return;
        }
    }
    transition();
}

void BettingStreet::executeStreet() {
    Street street = gameData.getStreet();

    cout << "--------------------------------------------------------------\n";
    cout << "(+) State Manager: Entering the " << PrintUtil::streetToString(street) << "\n" << endl;

    // Deal the board and players
    switch(street) {
        case Street::PRE_FLOP: 
            controller.getDealerManager().dealGamePlayers();
            controller.getActionManager().handleBlinds();
            break;
        case Street::FLOP:
            controller.getDealerManager().dealBoard(3);
            break;
        default:
            controller.getDealerManager().dealBoard(1);           
    }

    PrintUtil::printPlayers(gameData);

    // Set the early position to act
    controller.getPositionManager().setEarlyPositionToAct();
    
    // Betting action loop
    while (!controller.isBettingStreetComplete()) {
        auto id = gameData.getCurPlayer()->getId();

        // Display possible actions for the current player to act
        controller.getActionManager().generatePossibleActionsForCurPlayer();
        controller.getIOManager().displayPossibleActionsStdOut();

        // Fetch action from the client
        auto [type, amount] = controller.getIOManager().getPlayerActionStdIn();
        controller.getActionManager().addNewAction(id, type, amount);

        // Update player to act
        if (controller.isBettingStreetComplete()) break;
        controller.getPositionManager().updatePlayerToAct();
    }

    // Calculate pots from the betting street
    controller.getPotManager().calculatePots();
}

void BettingStreet::transition() {
    controller.getStateManager().setState(make_unique<Winner>(gameData, controller));
 }