#include "../../include/Utils/GameUtil.h"

vector<shared_ptr<Player>>::const_iterator GameUtil::findPlayerIt(GameData& gameData, string idOrName) {
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

void GameUtil::setPlayerInitialToCurChips(GameData& gameData) {
    auto players = gameData.getPlayers();
    for (auto& player : players) {
        player->setInitialChips(player->getCurChips());
    }
}

void GameUtil::resetPlayerRecentBets(GameData& gameData) {
    auto players = gameData.getPlayers();
    for (auto& player : players) { 
        player->setRecentBet(0);
    }
}

void GameUtil::setInHandStatusForPlayers(GameData& gameData) {
    auto players = gameData.getPlayers();
    for (auto& player : players) { 
        player->setPlayerStatus(PlayerStatus::IN_HAND);
    }
}

void GameUtil::clearPlayerHands(GameData& gameData) {
    auto& players = gameData.getPlayers();
    for (auto& player: players) {
        player->clearHand();
    }
}

vector<string> GameUtil::getPlayerIds(GameData& gameData) {
    vector<string> playerIds;
    for (const auto& player : gameData.getPlayers()) playerIds.push_back(player->getId());
    return playerIds;
}

vector<string> GameUtil::getListofNames(GameData& gameData) {
    vector<string> playerNames;
    for (const auto& player : gameData.getPlayers()) playerNames.push_back(player->getName());
    return playerNames;
}

vector<Position> GameUtil::getListOfPositions(GameData& gameData) {
    vector<Position> positions;
    auto players = gameData.getPlayers();
    for (const auto& player : players) {
        positions.emplace_back(player->getPosition());
    }
    return positions;
}

string GameUtil::getPlayerNameFromId(GameData& gameData, string id) {
    auto player = getPlayer(gameData, id);
    return player->getName();
}

shared_ptr<Player> GameUtil::getPlayer(GameData& gameData, string idOrName) {
    auto it = findPlayerIt(gameData, idOrName);
    return (it != gameData.getPlayers().end())? (*it) : nullptr;
}

bool GameUtil::isPlayerBigBlind(GameData& gameData, string idOrName) {
    return (idOrName == gameData.getBigBlindId());
}

HandCategory GameUtil::getPlayerHandCategory(GameData& gameData, string idOrName) {
    auto player = getPlayer(gameData, idOrName);
    return player->getHandCategory();
}

vector<Card> GameUtil::getPlayerBestFiveCards(GameData& gameData, string idOrName) {
    auto player = getPlayer(gameData, idOrName);
    return player->getBestFiveCards();
}

size_t GameUtil::getPlayerInitialChips(GameData& gameData, string idOrName) {
    auto player = getPlayer(gameData, idOrName);
    return player->getInitialChips();
}

size_t GameUtil::getBigStackAmongOthers(GameData& gameData, string idOrName) {
    auto skipPlayer = getPlayer(gameData, idOrName);
    auto players = gameData.getPlayers();

    size_t bigStack = 0;
    for (const auto& player : players) {
        if (player == skipPlayer) continue;
        bigStack = max(bigStack, player->getInitialChips());
    }

    return bigStack;
}

vector<string> GameUtil::getRankedNames(GameData& gameData) {
    vector<string> rankedNames;
    vector<string> rankedIds = gameData.getRankedIds();
    for (auto& id : rankedIds) {
        auto player = getPlayer(gameData, id);
        rankedNames.emplace_back(player->getName());
    }
    return rankedNames;
}

shared_ptr<Player> GameUtil::getEarlyPosition(GameData& gameData) {
    auto players = gameData.getPlayers();
    return players.front();
}

shared_ptr<Player> GameUtil::getNextPlayerInHand(GameData& gameData, string idOrName) {
    shared_ptr<Player> prev = getPlayer(gameData, idOrName);
    vector<shared_ptr<Player>> players = gameData.getPlayers();

    auto it = find(players.begin(), players.end(), prev);

    if (it != players.end()) {
        do {
            ++it;
            // Wrap to the beginning if needed
            if (it == players.end()) it = players.begin();

            // Check if the player is IN_HAND
            if ((*it)->getPlayerStatus() == PlayerStatus::IN_HAND) return (*it);
        } while (it != find(players.begin(), players.end(), prev));
    }
    
    return nullptr;
}

vector<shared_ptr<Player>> GameUtil::getPreFlopOrderPlayers(GameData& gameData) {
    auto bigBlindId = gameData.getBigBlindId();
    auto preFlopOrder = gameData.getPlayers();

    auto bigBlindIt = std::find_if(preFlopOrder.begin(), preFlopOrder.end(),
                                    [&bigBlindId] (const shared_ptr<Player>& player) {
                                        return player->getId() == bigBlindId;
                                    });
    
    if (bigBlindIt != preFlopOrder.end()) {
        rotate(preFlopOrder.begin(), std::next(bigBlindIt), preFlopOrder.end());
    }

    return preFlopOrder;
}

vector<shared_ptr<Player>> GameUtil::getOccupiedPlayers(GameData& gameData) {
    auto gamePlayers = gameData.getPlayers();
    vector<shared_ptr<Player>> occupiedPlayers;

    copy_if(gamePlayers.begin(), gamePlayers.end(), back_inserter(occupiedPlayers),
            [](const shared_ptr<Player>& player) {
                return player->getPosition() != Position::LOBBY;
            });

    return occupiedPlayers;
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

int GameUtil::getBoardSize(GameData& gameData) {
    return gameData.getBoard().getBoardSize();
}

int GameUtil::getNumActionsInTimeline(GameData& gameData) { 
    return gameData.getActionTimeline().size();
}

ActionType GameUtil::getActiveActionType(GameData& gameData) { 
    return gameData.getActiveAction()->getActionType();
}

size_t GameUtil::getActiveActionAmount(GameData& gameData) {
    return gameData.getActiveAction()->getAmount();
}

bool GameUtil::isIdInCurPot(GameData& gameData, string id) {
    auto curPot = gameData.getCurPot();
    return (curPot->isIdEligible(id));
}

size_t GameUtil::getNumPots(GameData& gameData) {
    return gameData.getPots().size();
}