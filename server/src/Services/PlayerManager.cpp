#include "../../include/Services/PlayerManager.h"
#include "../../include/Utils/PlayerUtil.h"
#include "../../include/Utils/GameUtil.h"

PlayerManager::PlayerManager(GameData& gameData) : gameData(gameData) {}

bool PlayerManager::addNewPlayer(tuple<string, uint32_t, string> newPlayerInfo) {
    auto [name, chips, playerId] = newPlayerInfo;
    shared_ptr<Player> player = make_shared<Player>(name, chips, playerId);
    gameData.addPlayer(player);
    player->setPosition(Position::LOBBY);
    player->setPlayerStatus(PlayerStatus::WAITING);
    return true;
}

bool PlayerManager::addNewPlayers(vector<pair<string, uint32_t>> newPlayersInfo) {
    // cout << "(+) PlayerManager: addNewPlayers called.\n" << endl;
    for (auto& info : newPlayersInfo) {
        string name = info.first;
        uint32_t chips = info.second;
        string id = PlayerUtil::generateUUID();
        
        // Add the player to Game Data and set their position and status
        shared_ptr<Player> player = make_shared<Player>(name, chips, id);
        gameData.addPlayer(player);
        player->setPosition(Position::LOBBY);
        player->setPlayerStatus(PlayerStatus::WAITING);
    }
    return true;
}

bool PlayerManager::removeExistingPlayers(vector<string> playersIdOrName) {
    // cout << "(+) PlayerManager: removeExistingPlayer called.\n" << endl;
    for (auto& idOrName : playersIdOrName) {
        // Validate player existence
        auto player = GameUtil::getPlayer(gameData, idOrName);
        if (player == nullptr) return false;

        // Remove the player from Game Data
        gameData.removePlayer(player);
    }
    return true;
}

void PlayerManager::removeBrokePlayers() {
    auto players = gameData.getPlayers();
    for (const auto& player : players) {
        if (player->getCurChips() == 0) {
            // cout    << "(+) Player Manager: Removing the following player from the game due to insufficient chips: "
            //        << player->getName() << '\n' << endl;
            removeExistingPlayers({player->getId()});
        }
    }
}

void PlayerManager::removeAllPlayers() {
    gameData.removeAllPlayers();
}

vector<string> PlayerManager::getPlayerIds() {
    return GameUtil::getPlayerIds(gameData);
}

int PlayerManager::getNumPlayers() const {
    return gameData.getPlayers().size();
}