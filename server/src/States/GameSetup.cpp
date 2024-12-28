#include "../../include/States/GameSetup.h"
#include "../../include/States/BettingStreet.h"
#include "../../include/GameController.h"

void GameSetup::execute() {
    cout << "--------------------------------------------------------------\n";
    cout << "(+) StateManager: Entering the Game\n" << endl;

    // Remove players that do not have sufficient chips
    controller.getPlayerManager().removeBrokePlayers();

    // Player Addition and Removal
    while (!controller.isAtLeastTwoPlayers(gameData)) {
        
        while (!controller.isAtLeastTwoPlayers(gameData)){
            auto newPlayers = controller.getIOManager().addPlayersStdIn();
            if (newPlayers.size() != 0) controller.getPlayerManager().addNewPlayers(newPlayers);
        }
        cout << "\n";

        auto oldPlayers = controller.getIOManager().removePlayersStdIn();
        if (oldPlayers.size() != 0) controller.getPlayerManager().removeExistingPlayers(oldPlayers);
        cout << "\n";
    }

    // Assign positions, blinds and button to players
    controller.getPositionManager().allocatePositions();

    // Shuffle the deck
    controller.getDealerManager().resetDeck();

    // Transition to Betting Streets
    transition();
}

void GameSetup::transition() {
    controller.getStateManager().setState(make_unique<BettingStreet>(gameData, controller));
}