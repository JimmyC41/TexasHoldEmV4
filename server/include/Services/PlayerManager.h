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

    // Validation Helper Methods
    bool isValidName(const string& name);
public:
    PlayerManager(GameData& gameData);

    // Adds a new player given the name, chip_count and an session id
    bool addNewPlayer(tuple<string, uint32_t, string> newPlayerInfo);

    // Event: Triggered when a new client requests to enter the game during the Game Setup state
    // ToGameData: Adds a shared Player ptr to the gamePlayers vector
    // Returns true if player addition was successful
    bool addNewPlayers(vector<pair<string, uint32_t>> newPlayersInfo);

    // Event: Triggered when a new client requests to leave the game during the Game Setup state
    // ToGameData: Removes the player from vector<shared_ptr<Player>> gamePlayers
    // Returns true if player(s) removal was successful
    bool removeExistingPlayers(vector<string> playersIdOrName);

    // Event: Triggered at the beginning of the Game Setup state
    // To GameData: Removes players from the game that have 0 chips
    void removeBrokePlayers();

    void removeAllPlayers();
    vector<string> getPlayerIds();
    int getNumPlayers() const;
};

#endif