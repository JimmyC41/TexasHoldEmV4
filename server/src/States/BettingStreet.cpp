#include "../../include/States/BettingStreet.h"
#include "../../include/States/Winner.h"
#include "../../include/GameController.h"

void BettingStreet::execute() {
    for (int street = static_cast<int>(Street::PRE_FLOP);
            street <= static_cast<int>(Street::RIVER); ++street) {
        
        gameData.setCurStreet(static_cast<Street>(street));

        // Event Manager: Publish NewStreetEvent
        controller.getEventManager().publishNewStreetEvent();

        // Go to the betting street loop game logic
        executeStreet();

        // Early exit condition to Winner State if less than 2 players in hand
        if (controller.getActionManager().isShortPlayersInHand()) {
            transition();
            return;
        }
    }

    // Transition to the Winner State
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

            // Event Manager: Publish DealPlayersEvent
            controller.getEventManager().publishDealPlayersEvent();
            break;
        case Street::FLOP:
            controller.getDealerManager().dealBoard(3);

            // Event Manager: Publish DealBoardEvent
            controller.getEventManager().publishDealBoardEvent();
            break;
        default:
            controller.getDealerManager().dealBoard(1);

            // Event Manager: Publish DealBoardEvent
            controller.getEventManager().publishDealBoardEvent();
            break;         
    }

    // Set the early position to act
    controller.getPositionManager().setEarlyPositionToAct();
    
    // Betting action loop
    while (!controller.isBettingStreetComplete()) {
        // Get the player to act and determine possible actions
        auto id = gameData.getCurPlayer()->getId();
        controller.getActionManager().generatePossibleActionsForCurPlayer();

        // Event Manager: Publish NewPlayerToActEvent
        controller.getEventManager().publishNewPlayerToActEvent();

        // Request Manager: Fetch and process action from the client
        auto [type, amount] = controller.getRequestManager().getActionRequest();
        controller.getActionManager().addNewAction(id, type, amount);

        // Event Manager: Publish NewPlayerActionEvent
        controller.getEventManager().publishNewPlayerActionEvent();
        
        // Update the next player to act
        if (controller.isBettingStreetComplete()) break;
        controller.getPositionManager().updatePlayerToAct();
    }

    // Calculate pots from the betting street
    controller.getPotManager().calculatePots();

    // Event Manager: Publish PotUpdateEvent
    controller.getEventManager().publishPotUpdateEvent();
}

void BettingStreet::transition() {
    controller.getStateManager().setState(make_unique<Winner>(gameData, controller));
 }