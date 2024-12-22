#include "../../include/Shared/GameData.h"

void GameData::addPlayer(shared_ptr<Player> player) {
    gamePlayers.push_back(player);
}

vector<shared_ptr<Player>> GameData::getPreFlopOrderPlayers() {
    auto preFlopOrder = getPlayers();
    auto bigBlindId = getBigBlindId();

    auto bigBlindIt = std::find_if(preFlopOrder.begin(), preFlopOrder.end(),
                                    [&bigBlindId] (const shared_ptr<Player>& player) {
                                        return player->getId() == bigBlindId;
                                    });
    
    if (bigBlindIt != preFlopOrder.end()) {
        std::rotate(preFlopOrder.begin(), std::next(bigBlindIt), preFlopOrder.end());
    }

    return preFlopOrder;
}

void GameData::setPlayerPosition(string id, Position position) {
    auto player = getPlayer(id);
    if (player != nullptr) {
        player->setPosition(position);
        if (position == Position::BIG_BLIND) bigBlindId = player->getId();
    }
}

shared_ptr<Player> GameData::getPlayer(string idOrName) const {
    auto it = std::find_if(gamePlayers.begin(), gamePlayers.end(),
                            [&idOrName] (const shared_ptr<Player>& player) {
                                return ((player->getId() == idOrName) || (player->getName() == idOrName));
                            });

    return (it != gamePlayers.end())? (*it) : nullptr;
}

int GameData::getNumPlayers() const {
    return gamePlayers.size();
}

bool GameData::isPlayersDealt() const{
    for (const auto& player : gamePlayers) {
        if (player->getHand().size() != 2) return false;
    }
    return true;
}