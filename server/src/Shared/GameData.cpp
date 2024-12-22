#include "../../include/Shared/GameData.h"

void GameData::addPlayer(const shared_ptr<Player>& player) {
    gamePlayers.push_back(player);
}

void GameData::setRankedPlayerIds(const vector<string>& ids) {
    rankedPlayerIds = ids;
}

void GameData::setBigBlindId(const string& id) {
    bigBlindId = id;
}