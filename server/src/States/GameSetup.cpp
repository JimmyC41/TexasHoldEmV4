#include "../../include/States/GameSetup.h"
#include "../../include/States/BettingStreet.h"
#include "../../include/GameController.h"

constexpr int MIN_NUM_PLAYERS = 2;
constexpr int MAX_NUM_PLAYERS = 9;


void GameSetup::execute() {
    // cout << "--------------------------------------------------------------\n";
    // cout << "(+) StateManager: Entering the Game\n" << endl;

    // Process oustanding requests to leave the game
    while (!controller.getRequestManager().isLeaveQueueEmpty()) {

        auto request = controller.getRequestManager().getLeaveRequest();
        controller.getPlayerManager().removeExistingPlayers({request});
        controller.getPositionManager().allocatePositions();
    }

    // Process outstanding requests to join the game
    while (controller.getGameData().getNumPlayers() < MAX_NUM_PLAYERS) {
        while (!controller.getRequestManager().isJoinQueueEmpty() &&
            controller.getGameData().getNumPlayers() < MAX_NUM_PLAYERS) {
            
            auto request = controller.getRequestManager().getJoinRequest();
            controller.getPlayerManager().addNewPlayers({request});
            controller.getPositionManager().allocatePositions();
        }

        // Early exit if there are at least 2 players to start the game!
        if (controller.getGameData().getNumPlayers() >= MIN_NUM_PLAYERS) break;
    }

    // Shuffle the deck
    controller.getDealerManager().resetDeck();

    // EVENT MANAGER: Publish PlayersUpdateEvent
    controller.getEventManager().publishPlayersUpdateEvent();

    // Transition to betting street
    transition();
}



// void GameSetup::execute() {
//     cout << "--------------------------------------------------------------\n";
//     cout << "(+) StateManager: Entering the Game\n" << endl;

//     // Remove players that do not have sufficient chips
//     controller.getPlayerManager().removeBrokePlayers();
//     controller.getPositionManager().allocatePositions();

//     // Player Addition and Removal
//     // Player Manager adds the player, sets position to lobby and status to waiting
//     // Position Manager assigns the player an open seat and updates the pointers to blinds and the button
//     while (!controller.isAtLeastTwoPlayers(gameData)) {
//         while (!controller.isAtLeastTwoPlayers(gameData)){
//             auto newPlayers = controller.getIOManager().addPlayersStdIn();
//             if (newPlayers.size() != 0) {
//                 controller.getPlayerManager().addNewPlayers(newPlayers);
//                 controller.getPositionManager().allocatePositions();
//             }
//         }
//         cout << "\n";

//         auto oldPlayers = controller.getIOManager().removePlayersStdIn();
//         if (oldPlayers.size() != 0) {
//             controller.getPlayerManager().removeExistingPlayers(oldPlayers);
//             controller.getPositionManager().allocatePositions();
//         }
//         cout << "\n";
//     }
    
//     // Shuffle the deck
//     controller.getDealerManager().resetDeck();

//     // Transition to Betting Streets
//     transition();
// }

void GameSetup::transition() {
    controller.getStateManager().setState(make_unique<BettingStreet>(gameData, controller));
}