#ifndef RPC_VALIDATOR
#define RPC_VALIDATOR

#include "../Shared/GameData.h"
#include <mutex>

class RPCValidator { 
    GameData& gameData;
    mutable mutex gameDataMtx;

public:
    RPCValidator(GameData& gd);

    // Returns FALSE if:
    // Game is full, name is invalid, chips is below min buyin
    bool canJoin(const string& name, const uint32_t& chips) const;

    // Returns FALSE if player does not exist in the game
    bool canLeave(const string& name) const;

};

#endif