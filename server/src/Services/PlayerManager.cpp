#include "../../include/Services/PlayerManager.h"
#include "../../include/Utils/PlayerUtil.h"
#include "../../include/Utils/GameUtil.h"

PlayerManager::PlayerManager(GameData& gameData) : gameData(gameData) {}

bool PlayerManager::addNewPlayer(tuple<string, uint32_t, string> newPlayerInfo)
{
    auto [name, chips, playerId] = newPlayerInfo;
    unique_ptr<Player> player = make_unique<Player>(name, chips, playerId);
    player->setPosition(Position::LOBBY);
    player->setPlayerStatus(PlayerStatus::WAITING);

    // Transfer ownership to Game Data shared state
    gameData.addPlayer(std::move(player));
    return true;
}

bool PlayerManager::addNewPlayers(vector<pair<string, uint32_t>> newPlayersInfo)
{
    for (auto& info : newPlayersInfo)
    {
        string name = info.first;
        uint32_t chips = info.second;
        string id = PlayerUtil::generateUUID();
        unique_ptr<Player> player = make_unique<Player>(name, chips, id);
        player->setPosition(Position::LOBBY);
        player->setPlayerStatus(PlayerStatus::WAITING);

        // Transfer ownership to Game Data shared state
        gameData.addPlayer(std::move(player));
    }
    return true;
}

bool PlayerManager::removeExistingPlayers(vector<string> playersIdOrName)
{
    for (auto& idOrName : playersIdOrName) {
        auto player = GameUtil::getPlayer(gameData, idOrName);
        if (player == nullptr) return false;

        // Remove the player from Game Data
        gameData.removePlayer(player);
    }
    return true;
}

void PlayerManager::removeBrokePlayers() {
    auto players = gameData.getRawPlayers();

    // Filter players with no chips
    vector<Player*> playersWithNoChips;
    std::copy_if
    (
        players.begin(),
        players.end(),
        std::back_inserter(playersWithNoChips),
        [] (const Player* player)
        {
            return player && player->getCurChips() == 0;
        }
    );

    // Fetch the ids of filtered players
    vector<string> idsOfNoChips;
    std::transform
    (
        playersWithNoChips.begin(),
        playersWithNoChips.end(),
        std::back_inserter(idsOfNoChips),
        [] (const Player* player)
        {
            return player->getId();
        }
    );

    // Remove players with no chips
    removeExistingPlayers(idsOfNoChips);
}

void PlayerManager::removeAllPlayers()
{
    gameData.removeAllPlayers();
}

vector<string> PlayerManager::getPlayerIds()
{
    return GameUtil::getPlayerIds(gameData);
}

int PlayerManager::getNumPlayers() const
{
    return gameData.getNumPlayers();
}