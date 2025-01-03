#include "../../include/Services/RPCValidator.h"
#include "../../include/Utils/GameUtil.h"
#include "../../include/Utils/PlayerUtil.h"

constexpr int MAX_NUM_PLAYERS = 9;

RPCValidator::RPCValidator(GameData& gd) : 
    gameData(gd),
    gameDataMtx()
    {}

bool RPCValidator::canJoin(const string& name, const uint32_t& chips) const {
    lock_guard<mutex> lock(gameDataMtx);

    if (!PlayerUtil::isValidName(name)) {
        cout << "(+) RPC Validator: Name is invalid. "
             << "Join Request denied.\n" << endl;
        return false;
    }

    if (!PlayerUtil::isMinBuyin(gameData.getBigBlind(), chips)) {
        cout << "(+) RPC Validator: Minimum buyin requirement not met. "
             << "Join Request denied.\n" << endl;
        return false;
    }


    if (gameData.getNumPlayers() >= MAX_NUM_PLAYERS) {
        cout << "(+) RPC Validator: Maximum number of players reached. "
             << "Join Request denied.\n" << endl;
        return false;
    }

    if (GameUtil::isPlayerExists(gameData, name)) {
        cout << "(+) RPC Validator: Player with the same name already exists. "
             << "Join Request denied.\n" << endl;
        return false;
    }

    cout << "(+) RPC Validator: Join Request accepted.\n" << endl;
    return true;
}

bool RPCValidator::canLeave(const string& name) const {
    lock_guard<mutex> lock(gameDataMtx);

    if (!GameUtil::isPlayerExists(gameData, name)) {
        cout << "(+) RPC Validator: Non existent player. "
             << "Leave Request denied.\n" << endl;
        return false;
    }

    cout << "(+) RPC Validator: Leave Request accepted.\n" << endl;
    return true;
}