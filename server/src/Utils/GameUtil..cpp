#include "../../include/Utils/GameUtil.h"

vector<shared_ptr<Player>>::const_iterator GameUtil::findPlayerIt
(
    GameData& gameData, string idOrName
) {
    auto& players = gameData.getPlayers();
    return find_if(players.begin(), players.end(),
                    [&idOrName](const shared_ptr<Player>& player) {
                        return (player->getId() == idOrName || player->getName() == idOrName);
                    });
}

void GameUtil::setPlayerPosition(GameData& gameData, string id, Position position) {
    auto player = getPlayer(gameData, id);
    if (player != nullptr) {
        player->setPosition(position);
        if (position == Position::BIG_BLIND) gameData.setBigBlindId(player->getId());
    }
}

void GameUtil::clearPlayerHands(GameData& gameData) {
    auto& players = gameData.getPlayers();
    for (auto& player: players) {
        player->clearHand();
    }
    cout << "All player hands cleared." << endl;
}

vector<string> GameUtil::getPlayerIds(GameData& gameData) {
    vector<string> playerIds;
    for (const auto& player : gameData.getPlayers()) playerIds.push_back(player->getId());
    return playerIds;
}

shared_ptr<Player> GameUtil::getPlayer(GameData& gameData, string idOrName) {
    auto it = findPlayerIt(gameData, idOrName);
    return (it != gameData.getPlayers().end())? (*it) : nullptr;
}

vector<shared_ptr<Player>> GameUtil::getPreFlopOrderPlayers(GameData& gameData) {
    auto bigBlindId = gameData.getBigBlindId();
    auto preFlopOrder = gameData.getPlayers();
    cout << "getPreFlopOrderPlayers called. Total players: " << preFlopOrder.size() << endl;

    if (preFlopOrder.empty()) {
        cout << "Error: No players in game data!" << endl;
    }

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