#include "../../include/Services/RPCValidator.h"
#include "../../include/Utils/GameUtil.h"
#include "../../include/Utils/PlayerUtil.h"

constexpr int MAX_NUM_PLAYERS = 9;

RPCValidator::RPCValidator(GameData& gd) : 
    gameData(gd),
    gameDataMtx() {}

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

bool RPCValidator::canLeave(const string& playerId) const {
    lock_guard<mutex> lock(gameDataMtx);

    if (!GameUtil::isPlayerExists(gameData, playerId)) {
        cout << "(+) RPC Validator: Non existent player. "
             << "Leave Request denied.\n" << endl;
        return false;
    }

    cout << "(+) RPC Validator: Leave Request accepted.\n" << endl;
    return true;
}

bool RPCValidator::isPossibleAction(const string& id, ActionType type, const uint32_t& amount) const {
    lock_guard<mutex> lock(gameDataMtx);

    if (GameUtil::getCurPlayerId(gameData) != id &&
        GameUtil::getCurPlayerName(gameData) != id) {
        cout << "(+) RPC Validator: Player is acting out of turn. "
             << "Action Request denied.\n" << endl;
        return false;
    }

    if (!GameUtil::isAPossibleAction(gameData, type, amount)) {
        cout << "(+) RPC Validator: Requested action is not valid. "
             << "Action Request denied.\n" << endl;
        return false;
    }

    cout << "(+) RPC Validator: Action Request accepted.\n" << endl;
    return true;
}

bool RPCValidator::isInGame(const string& idOrName) {
    lock_guard<mutex> lock(gameDataMtx);
    return GameUtil::isPlayerExists(gameData, idOrName);
}