#include "../../include/Utils/GameUtil.h"

void GameUtil::setPlayerPosition(GameData& gameData, string id, Position position) {
    auto player = getPlayer(gameData, id);
    if (player != nullptr) {
        player->setPosition(position);
        if (position == Position::BIG_BLIND) gameData.setBigBlindId(player->getId());
    }
}

vector<string>& GameUtil::getPlayerIds(GameData& gameData) {
    vector<string> playerIds;
    for (const auto& player : gameData.getPlayers()) playerIds.push_back(player->getId());
    return playerIds;
}

shared_ptr<Player> GameUtil::getPlayer(GameData& gameData, string idOrName) {
    auto it = std::find_if(gameData.getPlayers().begin(), gameData.getPlayers().end(),
                            [&idOrName] (const shared_ptr<Player>& player) {
                                return ((player->getId() == idOrName) || (player->getName() == idOrName));
                            });
    return (it != gameData.getPlayers().end())? (*it) : nullptr;
}

vector<shared_ptr<Player>> GameUtil::getPreFlopOrderPlayers(GameData& gameData) {
    auto preFlopOrder = gameData.getPlayers();
    auto bigBlindId = gameData.getBigBlindId();

    auto bigBlindIt = std::find_if(preFlopOrder.begin(), preFlopOrder.end(),
                                    [&bigBlindId] (const shared_ptr<Player>& player) {
                                        return player->getId() == bigBlindId;
                                    });
    
    if (bigBlindIt != preFlopOrder.end()) {
        std::rotate(preFlopOrder.begin(), std::next(bigBlindIt), preFlopOrder.end());
    }

    return preFlopOrder;
}

int GameUtil::getNumPlayers(GameData& gameData) {
    return gameData.getPlayers().size();
}

bool GameUtil::isPlayersDealt(GameData& gameData) {
    for (const auto& player : gameData.getPlayers()) {
        if (player->getHand().size() != 2) return false;
    }
    return true;
}