#include "../../include/Shared/GameData.h"

void GameData::addPlayer(const shared_ptr<Player>& player) {
    gamePlayers.push_back(player);
}

bool GameData::removePlayer(const shared_ptr<Player>& player) {
    auto it = find(gamePlayers.begin(), gamePlayers.end(), player);
    if (it != gamePlayers.end()) {
        gamePlayers.erase(it);
        return true;
    } else {
        cout << "Player cannot be found for removal!" << '\n' << endl;
        return false;
    }
}

void GameData::setLastPlayerAsButton() {
    if (!gamePlayers.empty()) {
        auto& buttonPlayer = gamePlayers.back();
        buttonId = buttonPlayer->getId();
    }
}

void GameData::sortPlayersByPosition() {
    sort(gamePlayers.begin(), gamePlayers.end(),
        [](const shared_ptr<Player>& a, const shared_ptr<Player>& b) {
            return static_cast<int>(a->getPosition()) < static_cast<int>(b->getPosition());
        });
}