#include "../../include/Shared/GameData.h"

void GameData::addPlayer(shared_ptr<Player> player) {
    gamePlayers.push_back(player);
}

void GameData::setBigBlindId(string id) {
    bigBlindId = id;
}