#ifndef POSITION_MANAGER_H
#define POSITION_MANAGER_H

#include "Player.h"

class PositionManager {
private:
    shared_ptr<Player> playerToAct;

public:
    // Event: Triggered when a client request to add a player is received in the Game Setup state
    // To GameData: Updates the Position attribute of the Player object and sets the buttonId
    // From GameData: Fetches vector<shared_ptr<Player>> gamePlayers
    void allocatePositions();

    // Event: Triggered at the start of the Round End state.
    // To GameData: Updates the Position attribute of all players in the gamePlayers vector
    // From GameData: Fetches vector<shared_ptr<Player>> gamePlayers
    void rotatePositions();

    // Event: Triggered after a client betting action is receieved in the Street In Progress state
    // To GameData: Updates curPlayerId and the isActing attribute of the Player object
    // From GameData: Fetches vector<shared_ptr<Player>> gamePlayers
    void updatePlayerToAct();

};

#endif