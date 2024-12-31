#include "../../include/States/GameSetup.h"
#include "../../include/States/BettingStreet.h"
#include "../../include/GameController.h"

void GameSetup::execute() {
    cout << "--------------------------------------------------------------\n";
    cout << "(+) StateManager: Entering the Game\n" << endl;

    // Remove players that do not have sufficient chips
    controller.getPlayerManager().removeBrokePlayers();
    controller.getPositionManager().allocatePositions();

    // Player Addition and Removal
    // Player Manager adds the player, sets position to lobby and status to waiting
    // Position Manager assigns the player an open seat and updates the pointers to
    // blinds and the button
    while (!controller.isAtLeastTwoPlayers(gameData)) {
        
        while (!controller.isAtLeastTwoPlayers(gameData)){
            auto newPlayers = controller.getIOManager().addPlayersStdIn();
            if (newPlayers.size() != 0) {
                controller.getPlayerManager().addNewPlayers(newPlayers);
                controller.getPositionManager().allocatePositions();
            }
        }
        cout << "\n";

        auto oldPlayers = controller.getIOManager().removePlayersStdIn();
        if (oldPlayers.size() != 0) {
            controller.getPlayerManager().removeExistingPlayers(oldPlayers);
            controller.getPositionManager().allocatePositions();
        }
        cout << "\n";
    }
    // Shuffle the deck
    controller.getDealerManager().resetDeck();

    PrintUtil::printPlayers(gameData);

    // Transition to Betting Streets
    transition();
}

void GameSetup::transition() {
    controller.getStateManager().setState(make_unique<BettingStreet>(gameData, controller));
}