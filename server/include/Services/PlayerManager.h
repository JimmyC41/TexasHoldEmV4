#ifndef PLAYER_MANAGER_H
#define PLAYER_MANAGER_H

#include "../Entities/Player.h"

class PlayerManager {
private:
public:
    // Event: Triggered when a new client requests to enter the game during the Game Setup state
    // ToGameData: Adds a new Player object to the vector<shared_ptr<Player>> gamePlayers
    // * to implement the ClientAction object
    void addNewPlayer(ClientAction action);

    // Event: Triggered when a new client requests to leave the game during the Game Setup state
    // ToGameData: Removes the player from vector<shared_ptr<Player>> gamePlayers
    // * to implement the ClientAction object
    void removeExistingPlayer(ClientAction action);

    int getNumPlayers() const;
};

#endif