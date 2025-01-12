#ifndef RPC_VALIDATOR
#define RPC_VALIDATOR

#include "../Shared/GameData.h"
#include <mutex>

class RPCValidator { 
    GameData& gameData;
    mutable mutex gameDataMtx;

public:
    RPCValidator(GameData& gd);

    // Checks if a player exists in the game
    bool isInGame(const string& idOrName);

    // Checks if a player can join the game
    // Conditions: Game is not full, name is valid, chips is above min buyin
    bool canJoin(const string& name, const uint32_t& chips) const;

    // Checks if a player can leave the game
    bool canLeave(const string& playerId) const;

    // Checks if the client is the player to act and their action is valid
    bool isPossibleAction(const string& id, ActionType type, const uint32_t& amount) const;
};

#endif