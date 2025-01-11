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

    /* Validation Helper Method */
    bool isValidName(const string& name);

public:
    PlayerManager(GameData& gameData);

    /**
     * Adds a new player, provided a name, initial chip count and session id.
     * Creates a unique player ptr and transfer ownership to Game Data.
     */
    bool addNewPlayer(tuple<string, uint32_t, string> newPlayerInfo);

    /**
     * Given a vector of session tokens, removes players from the game.
     */
    bool removeExistingPlayers(vector<string> playersIdOrName);

    /**
     * Removes players from the game that have 0 chips.
     */
    void removeBrokePlayers();

    /**
     * Removes ALL players from the game for cleanup in unit tests.
     */
    void removeAllPlayers();

    /**
     * Retrieves player Ids for all players in the game.
     */
    vector<string> getPlayerIds();

    /**
     * Gets the number of players in the game.
     */
    int getNumPlayers() const;

    /**
     * Deprecated method. Use addNewPlayer() instead.
     * Implemented before session tokens. Session tokens are generated
     * by the method, instead of being parsed in as a parameter.
     * Only used for old unit tests.
     */
    bool addNewPlayers(vector<pair<string, uint32_t>> newPlayersInfo);
};

#endif