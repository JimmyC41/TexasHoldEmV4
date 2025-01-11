#include "../../include/Shared/GameData.h"

void GameData::addPlayer(const shared_ptr<Player>& player) {
    gamePlayers.push_back(player);
}

void GameData::removePlayer(const shared_ptr<Player>& player) {
    auto it = find(gamePlayers.begin(), gamePlayers.end(), player);
    if (it != gamePlayers.end()) gamePlayers.erase(it);
}

void GameData::setLastPlayerAsButton() { 
    if (!gamePlayers.empty()) setButtonPlayer(gamePlayers.back());
}

void GameData::sortPlayersByPosition() {
    sort(gamePlayers.begin(), gamePlayers.end(),
        [](const shared_ptr<Player>& a, const shared_ptr<Player>& b) {
            return static_cast<int>(a->getPosition()) < static_cast<int>(b->getPosition());
        });
}

void GameData::reset() {
    curPlayer.reset();
    smallBlindPlayer.reset();
    bigBlindPlayer.reset();
    buttonPlayer.reset();
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