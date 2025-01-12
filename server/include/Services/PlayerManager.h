#ifndef PLAYER_MANAGER_H
#define PLAYER_MANAGER_H

#include "../Entities/Player.h"
#include "../Shared/GameData.h"

#include <vector>
#include <string>
#include <iostream>
#include <memory>
using namespace std;

class PlayerManager {
private:
    GameData& gameData;

    /* Validation Helper Methods */
    bool isValidName(const string& name);

public:
    PlayerManager(GameData& gameData);

    /**
     * Called when a new client requests to join the game
     * Adds the player to the Game if the player does not exist
     */
    bool addNewPlayer(tuple<string, uint32_t, string> newPlayerInfo);

    /**
     * Called when a new client requests to leave the game
     * Removes the player if the player exists
     */
    bool removeExistingPlayers(vector<string> playersIdOrName);

    /**
     * Called in the beginning of the Game Setup state
     * Removes players from the game that have 0 chips
     */
    void removeBrokePlayers();

    // Test Helper Methods
    void removeAllPlayers();
    vector<string> getPlayerIds();
    int getNumPlayers() const;

    /**
     * Deprecated method to add players ot the game *IGNORE*
     */
    bool addNewPlayers(vector<pair<string, uint32_t>> newPlayersInfo);
};

#endif