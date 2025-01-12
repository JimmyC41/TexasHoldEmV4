#include "../../include/States/GameSetup.h"
#include "../../include/States/BettingStreet.h"
#include "../../include/GameController.h"

#include <chrono>
#include <thread>

constexpr int MIN_NUM_PLAYERS = 2;
constexpr int MAX_NUM_PLAYERS = 9;


void GameSetup::execute() {
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
            controller.getPlayerManager().addNewPlayer({request});
            controller.getPositionManager().allocatePositions();
        }

        // Early exit if there are at least 2 players to start the game!
        if (controller.getGameData().getNumPlayers() >= MIN_NUM_PLAYERS) break;
    }

    // Shuffle the deck
    controller.getDealerManager().resetDeck();

    // Publish PlayersUpdateEvent
    controller.getEventManager().publishPlayersUpdateEvent();

    // Transition to betting street
    transition();
}

void GameSetup::transition() {
    controller.getStateManager().setState(make_unique<BettingStreet>(gameData, controller));
}