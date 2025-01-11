#include "../../include/Shared/GameData.h"

#include <assert.h>

void GameData::addPlayer(unique_ptr<Player> player)
{
    gamePlayers.emplace_back(std::move(player));
}

void GameData::removePlayer(Player* player) {
    auto it = std::find_if
    (
        gamePlayers.begin(),
        gamePlayers.end(),
        [&player] (const unique_ptr<Player>& p) {
            return p.get() == player;
        }
    );

    if (it != gamePlayers.end())
    {
        cout << "Removing player: " << (*it)->getName() << endl;
        gamePlayers.erase(it);
    } else {
        cerr << "Player not found for removal?" << endl;
    }

    for (auto& p : gamePlayers) {
        assert(p.get() != player && "Dangling pointer deteceted!");
    }
}

void GameData::sortPlayersByPosition()
{
    sort
    (
        gamePlayers.begin(),
        gamePlayers.end(),
        [](const unique_ptr<Player>& a, const unique_ptr<Player>& b)
        {
            return static_cast<int>(a->getPosition()) < static_cast<int>(b->getPosition());
        }
    );
}

void GameData::setLastPlayerAsButton()
{ 
    if (!gamePlayers.empty())
    {
        setButtonPlayer(gamePlayers.back().get());
    }
}

void GameData::setCurPlayer(Player* player)
{
    curPlayer = player;
}

void GameData::setSmallBlindPlayer(Player* player)
{
    smallBlindPlayer = player;
}

void GameData::setBigBlindPlayer(Player* player)
{
    bigBlindPlayer = player;
}

void GameData::setButtonPlayer(Player* player)
{
    buttonPlayer = player;
}

void GameData:: removeAllPlayers()
{
    gamePlayers.clear();
}

Player* GameData::getCurPlayer()
{
    return curPlayer;
}

Player* GameData::getSmallBlindPlayer()
{
    return smallBlindPlayer;
}
   
Player* GameData::getBigBlindPlayer()
{
    return bigBlindPlayer;
}

Player* GameData::getButtonPlayer()
{
    return buttonPlayer;
}

const vector<unique_ptr<Player>>& GameData::getPlayers() const
{
    return gamePlayers;
}

vector<Player*> GameData::getRawPlayers() const
{
    vector<Player*> sortedPlayers;
    sortedPlayers.reserve(gamePlayers.size());
    for (const auto& player : gamePlayers)
    {
        sortedPlayers.push_back(player.get());
    }
    return sortedPlayers;
}

int GameData::getNumPlayers() const
{
    return gamePlayers.size();
}

void GameData::reset() {
    curPlayer = nullptr;
    smallBlindPlayer = nullptr;
    bigBlindPlayer = nullptr;
    buttonPlayer = nullptr;
    gamePlayers.clear();
    rankedPlayerIds.clear();
    pots.clear();
    actionTimeline.clear();
    possibleActions.clear();
    deadChips = 0;
    curStreet = Street::NONE;
    board.resetBoard();
    smallBlind = 1;
    bigBlind = 2;
    activeAction.reset();
}