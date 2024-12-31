#include "../../include/Services/PlayerManager.h"

PlayerManager::PlayerManager(GameData& gameData) : gameData(gameData) {}

bool PlayerManager::addNewPlayers(vector<pair<string, size_t>> newPlayersInfo) {
    cout << "(+) PlayerManager: addNewPlayers called.\n" << endl;
    for (auto& info : newPlayersInfo) {
        shared_ptr<Player> player = make_shared<Player>(info.first, info.second);
        gameData.addPlayer(player);
        player->setPosition(Position::LOBBY);
        player->setPlayerStatus(PlayerStatus::WAITING);
    }
    return true;
}

bool PlayerManager::removeExistingPlayers(vector<string> playersIdOrName) {
    cout << "(+) PlayerManager: removeExistingPlayer called.\n" << endl;
    for (auto& idOrName : playersIdOrName) {
        // Fetch the shared ptr to the player we want to remove
        auto player = GameUtil::getPlayer(gameData, idOrName);

        // Attempt to remove this player from Game Data
        if (!gameData.removePlayer(player)) {
            cout << "Player removal process terminated!" << endl;
            continue;
        }
    }
    return true;
}

void PlayerManager::removeBrokePlayers() {
    auto players = gameData.getPlayers();
    for (const auto& player : players) {
        if (player->getCurChips() == 0) {
            cout    << "(+) Player Manager: Removing the following player from the game due to insufficient chips: "
                    << player->getName() << '\n' << endl;
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