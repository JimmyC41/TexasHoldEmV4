#include "../../include/Utils/GameUtil.h"
#include "../../include/GameController.h"

vector<shared_ptr<Player>>::const_iterator GameUtil::findPlayerIt(GameData& gameData, string idOrName) {
    auto& players = gameData.getPlayers();
    return find_if(players.begin(), players.end(),
                    [&idOrName](const shared_ptr<Player>& player) {
                        return (player->getId() == idOrName || player->getName() == idOrName);
                    });
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

vector<string> getPlayerNames(GameData& gameData) {
    vector<string> playerIds;
    for (const auto& player : gameData.getPlayers()) playerIds.push_back(player->getName());
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

vector<string> GameUtil::getNamesFromIds(GameData& gameData, const vector<string>& ids) {
    vector<string> names;
    for (auto& id : ids) names.push_back(GameUtil::getPlayerNameFromId(gameData, id));
    return names;
}


string GameUtil::getPlayerNameFromId(GameData& gameData, string id) {
    auto player = getPlayer(gameData, id);
    if (player == nullptr) return "Player does not exist!";
    return player->getName();
}

shared_ptr<Player> GameUtil::getPlayer(GameData& gameData, string idOrName) {
    auto it = findPlayerIt(gameData, idOrName);
    return (it != gameData.getPlayers().end())? (*it) : nullptr;
}

string GameUtil::getCurPlayerId(GameData& gameData) {
    return gameData.getCurPlayer()->getId();
}

string GameUtil::getCurPlayerName(GameData& gameData) {
    return gameData.getCurPlayer()->getName();
}

bool GameUtil::isPlayerBigBlind(GameData& gameData, string idOrName) {
    return (idOrName == gameData.getBigBlindPlayer()->getId());
}

bool GameUtil::isSmallBlindExists(GameData& gameData) {
    return (gameData.getSmallBlindPlayer() != nullptr);
}

bool GameUtil::isBigBlindExists(GameData& gameData) {
    return (gameData.getBigBlindPlayer() != nullptr);
}

bool GameUtil::isPlayerExists(GameData& gameData, string idOrName) {
    return (getPlayer(gameData, idOrName) != nullptr);
}

HandCategory GameUtil::getPlayerHandCategory(GameData& gameData, string idOrName) {
    auto player = getPlayer(gameData, idOrName);
    return player->getHandCategory();
}

vector<Card> GameUtil::getPlayerBestFiveCards(GameData& gameData, string idOrName) {
    auto player = getPlayer(gameData, idOrName);
    return player->getBestFiveCards();
}

uint32_t GameUtil::getPlayerInitialChips(GameData& gameData, string idOrName) {
    auto player = getPlayer(gameData, idOrName);
    return player->getInitialChips();
}

uint32_t GameUtil::getBigStackAmongOthers(GameData& gameData) {
    auto skipId = gameData.getCurPlayer()->getId();
    auto players = gameData.getPlayers();

    uint32_t bigStack = 0;
    for (const auto& player : players) {
        if (player->getId() == skipId) continue;
        if (player->getPlayerStatus() == PlayerStatus::FOLDED) continue;
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
    // Finds the first player that is in the hand
    auto players = gameData.getPlayers();
    auto it = find_if(players.begin(), players.end(),
        [](const shared_ptr<Player>& player) {
            return player->getPlayerStatus() == PlayerStatus::IN_HAND;
        });
    if (it != players.end()) {
        return (*it);
    }
    return nullptr;
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

vector<shared_ptr<Player>> GameUtil::getOccupiedPlayers(GameData& gameData) {
    auto gamePlayers = gameData.getPlayers();
    vector<shared_ptr<Player>> occupiedPlayers;

    copy_if(gamePlayers.begin(), gamePlayers.end(), back_inserter(occupiedPlayers),
            [](const shared_ptr<Player>& player) {
                return player->getPosition() != Position::LOBBY;
            });

    return occupiedPlayers;
}

vector<pair<string, uint32_t>> GameUtil::getPlayersCurChips(GameData& gameData) {
    vector<pair<string, uint32_t>> namesToChips;
    auto players = gameData.getPlayers();
    for (const auto& player : players) {
        namesToChips.push_back({player->getName(), player->getCurChips()});
    }
    return namesToChips;
}

int GameUtil::getNumPlayers(GameData& gameData) {
    return gameData.getPlayers().size();
}

int GameUtil::getNumPlayersInHand(GameData& gameData) {
    int numInHand = 0;
    auto players = gameData.getPlayers();
    for (const auto& player : players) {
        if (player->getPlayerStatus() == PlayerStatus::IN_HAND) numInHand++;
    }
    return numInHand;
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

uint32_t GameUtil::getActiveActionAmount(GameData& gameData) {
    return gameData.getActiveAction()->getAmount();
}

bool GameUtil::isIdInCurPot(GameData& gameData, string id) {
    auto curPot = gameData.getCurPot();
    return (curPot->isIdAContributor(id));
}

uint32_t GameUtil::getNumPots(GameData& gameData) {
    return gameData.getPots().size();
}

bool GameUtil::isShortPlayersInHand(GameData& gameData) {
    int numInHand = 0;
    auto players = gameData.getPlayers();
    for (const auto& player : players) { 
        if (player->getPlayerStatus() == PlayerStatus::IN_HAND) numInHand++;
    }
    return (numInHand < 2);
}

bool GameUtil::isActiveBetFoldedTo(GameData& gameData) {
    auto players = gameData.getPlayers();
    int numPlayers = players.size();
    int activeBet = 0;
    int folded = 0;

    for (const auto& player : players) {
        PlayerStatus status = player->getPlayerStatus();
        if (status == PlayerStatus::FOLDED) folded++;
        if (status == PlayerStatus::IN_HAND || status == PlayerStatus::ALL_IN_BET) activeBet++;
    }

    return (activeBet == 1 && (folded == (numPlayers - 1)));
}

bool GameUtil::isAPossibleAction(GameData& gameData, ActionType type, const uint32_t& amount) {
    auto possibleActions = gameData.getPossibleActions();

    for (auto const& possible : possibleActions) {
        // If action type matches, verify the amount is valid
        if (type == possible->getActionType()) {
            uint32_t primaryAmount = possible->getPrimaryAmount();
            uint32_t secondaryAmount = possible->getSecondaryAmount();

            if (secondaryAmount == 0) return (primaryAmount == amount);
            else return ((amount >= primaryAmount) && (amount <= secondaryAmount));
        }
    }

    // Action type not found
    return false;
}