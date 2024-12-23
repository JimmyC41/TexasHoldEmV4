#include "../../include/Shared/GameData.h"

void GameData::addPlayer(const shared_ptr<Player>& player) {
    gamePlayers.push_back(player);
}

bool GameData::removePlayer(const shared_ptr<Player>& player) {
    auto it = find(gamePlayers.begin(), gamePlayers.end(), player);
    if (it != gamePlayers.end()) {
        gamePlayers.erase(it);
        cout << "Player removed from Game Data: " << player->getName() << '\n' << endl;
        return true;
    } else {
        cout << "Player cannot be found for removal!" << '\n' << endl;
        return false;
    }
}

void GameData::removeAllPlayers() {
    gamePlayers.clear();
}

void GameData::setRankedPlayerIds(const vector<string>& ids) {
    rankedPlayerIds = ids;
}

void GameData::setBigBlindId(const string& id) {
    bigBlindId = id;
}

const vector<shared_ptr<Player>>& GameData::getPlayers() {
    return gamePlayers;
}