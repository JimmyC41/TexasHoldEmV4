#ifndef RPC_VALIDATOR
#define RPC_VALIDATOR

#include "../Shared/GameData.h"
#include <mutex>

class RPCValidator { 
    GameData& gameData;
    mutable mutex gameDataMtx;

public:
    RPCValidator(GameData& gd);

    // Returns FALSE if
    // Player does not exist in the game
    bool isInGame(const string& idOrName);

    // Returns FALSE if:
    // Game is full, name is invalid, chips is below min buyin
    bool canJoin(const string& name, const uint32_t& chips) const;

    // Returns FALSE if player does not exist in the game
    bool canLeave(const string& name) const;

    // Returns FALSE if:
    // Client is not the player to act (acting out of turn)
    // Type and amount are not among valid possible actions!
    bool isPossibleAction(const string& id, ActionType type, const uint32_t& amount) const;
};

#endif