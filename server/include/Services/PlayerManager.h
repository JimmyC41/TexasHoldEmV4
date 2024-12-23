#ifndef PLAYER_MANAGER_H
#define PLAYER_MANAGER_H

#include "../Entities/Player.h"
#include "../Shared/GameData.h"
#include "../Utils/GameUtil.h"

#include <vector>
#include <string>
#include <iostream>
#include <memory>
using namespace std;

class PlayerManager {
private:
    GameData& gameData;
public:
    PlayerManager(GameData& gameData);

    // Event: Triggered when a new client requests to enter the game during the Game Setup state
    // ToGameData: Adds a shared Player ptr to the gamePlayers vector
    // Returns true if player addition was successful
    bool addNewPlayers(vector<pair<string, size_t>> newPlayersInfo);

    // Event: Triggered when a new client requests to leave the game during the Game Setup state
    // ToGameData: Removes the player from vector<shared_ptr<Player>> gamePlayers
    // Returns true if player(s) removal was successful
    bool removeExistingPlayers(vector<string> playersIdOrName);

    void removeAllPlayers();
    vector<string> getPlayerIds();
    int getNumPlayers() const;
};

#endif