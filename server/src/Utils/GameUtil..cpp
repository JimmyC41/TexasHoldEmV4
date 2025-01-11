#include "../../include/Utils/GameUtil.h"
#include "../../include/GameController.h"

vector<unique_ptr<Player>>::const_iterator GameUtil::findPlayerIt(GameData& gameData, string idOrName)
{
    const auto& players = gameData.getPlayers();
    return find_if
    (
        players.begin(),
        players.end(),
        [&idOrName] (const unique_ptr<Player>& player)
        {
            return player && (player->getId() == idOrName || player->getName() == idOrName);
        }
    );
}

void GameUtil::clearPlayerHands(GameData& gameData)
{
    auto& players = gameData.getPlayers();
    for (auto& player: players)
    {
        player->clearHand();
    }
}

Player* GameUtil::getPlayer(GameData& gameData, const string& idOrName)
{
    auto& players = gameData.getPlayers();
    auto it = findPlayerIt(gameData, idOrName);
    return (it != players.end()) ? (it->get()) : nullptr;
}

int GameUtil::getNumPlayers(GameData& gameData)
{
    return gameData.getPlayers().size();
}


void GameUtil::setPlayerInitialToCurChips(GameData& gameData)
{
    auto& players = gameData.getPlayers();
    for (auto& player : players)
    {
        player->setInitialChips(player->getCurChips());
    }
}

void GameUtil::resetPlayerRecentBets(GameData& gameData)
{
    auto& players = gameData.getPlayers();
    for (auto& player : players)
    { 
        player->setRecentBet(0);
    }
}

void GameUtil::setInHandStatusForPlayers(GameData& gameData)
{
    auto& players = gameData.getPlayers();
    for (auto& player : players)
    { 
        player->setPlayerStatus(PlayerStatus::IN_HAND);
    }
}

vector<string> GameUtil::getPlayerIds(GameData& gameData)
{
    vector<string> playerIds;
    auto& players = gameData.getPlayers();
    for (const auto& player : players)
    {
        playerIds.push_back(player->getId());
    }
    return playerIds;
}

vector<string> getPlayerNames(GameData& gameData)
{
    vector<string> playerIds;
    auto& players = gameData.getPlayers();
    for (const auto& player : players)
    {
        playerIds.push_back(player->getName());
    }
    return playerIds;
}

vector<string> GameUtil::getListofNames(GameData& gameData)
{
    vector<string> playerNames;
    auto& players = gameData.getPlayers();
    for (const auto& player : players)
    {
        playerNames.push_back(player->getName());
    }
    return playerNames;
}

vector<Position> GameUtil::getListOfPositions(GameData& gameData)
{
    vector<Position> positions;
    auto& players = gameData.getPlayers();
    for (const auto& player : players) {
        positions.emplace_back(player->getPosition());
    }
    return positions;
}

string GameUtil::getPlayerNameFromId(GameData& gameData, string id)
{
    auto player = getPlayer(gameData, id);
    if (player == nullptr)
    {
        return "Player does not exist!";
    }
    return player->getName();
}

vector<string> GameUtil::getNamesFromIds(GameData& gameData, const vector<string>& ids)
{
    vector<string> names;
    for (auto& id : ids)
    {
        names.push_back(GameUtil::getPlayerNameFromId(gameData, id));
    }
    return names;
}

string GameUtil::getCurPlayerId(GameData& gameData)
{
    return gameData.getCurPlayer()->getId();
}

string GameUtil::getCurPlayerName(GameData& gameData)
{
    return gameData.getCurPlayer()->getName();
}

bool GameUtil::isSmallBlindExists(GameData& gameData)
{
    return (gameData.getSmallBlindPlayer() != nullptr);
}

bool GameUtil::isBigBlindExists(GameData& gameData)
{
    return (gameData.getBigBlindPlayer() != nullptr);
}

bool GameUtil::isPlayerBigBlind(GameData& gameData, string idOrName)
{
    return (idOrName == gameData.getBigBlindPlayer()->getId());
}

bool GameUtil::isPlayerExists(GameData& gameData, string idOrName)
{
    return (getPlayer(gameData, idOrName) != nullptr);
}

HandCategory GameUtil::getPlayerHandCategory(GameData& gameData, string idOrName)
{
    auto player = getPlayer(gameData, idOrName);
    return player->getHandCategory();
}

vector<Card> GameUtil::getPlayerBestFiveCards(GameData& gameData, string idOrName)
{
    auto player = getPlayer(gameData, idOrName);
    return player->getBestFiveCards();
}

uint32_t GameUtil::getPlayerInitialChips(GameData& gameData, string idOrName)
{
    auto player = getPlayer(gameData, idOrName);
    return player->getInitialChips();
}

uint32_t GameUtil::getBigStackAmongOthers(GameData& gameData)
{
    auto skipId = gameData.getCurPlayer()->getId();
    auto& players = gameData.getPlayers();

    uint32_t bigStack = 0;
    for (const auto& player : players) {
        if (player->getId() == skipId) continue;
        if (player->getPlayerStatus() == PlayerStatus::FOLDED) continue;
        bigStack = max(bigStack, player->getInitialChips());
    }
    return bigStack;
}

Player* GameUtil::getEarlyPosition(GameData& gameData)
{
    auto& players = gameData.getPlayers();
    auto it = find_if
    (
        players.begin(),
        players.end(),
        [] (const unique_ptr<Player>& player)
        {
            return player->getPlayerStatus() == PlayerStatus::IN_HAND;
        }
    );

    if (it != players.end()) return (it->get());
    else return nullptr;
}

Player* GameUtil::getNextPlayerInHand(GameData& gameData, string idOrName)
{
    auto& players = gameData.getPlayers();
    auto it = findPlayerIt(gameData, idOrName);

    if (it != players.end()) {
        auto startIt = it;
        do 
        {
            // Move iterator, wrap to the beginning if needed
            ++it;
            if (it == players.end()) it = players.begin();

            // Return the player if they are in the hand
            if ((it->get())->getPlayerStatus() == PlayerStatus::IN_HAND) return (it->get());
        }
        while (it != startIt);
    }
    return nullptr;
}

vector<Player*> GameUtil::getOccupiedPlayers(GameData& gameData)
{
    auto players = gameData.getRawPlayers();
    vector<Player*> occupiedPlayers;
    copy_if
    (
        players.begin(),
        players.end(),
        back_inserter(occupiedPlayers),
        [] (const Player* player) 
        {
            return player->getPosition() != Position::LOBBY;
        }
    );
    return occupiedPlayers;
}

vector<Player*> GameUtil::getPlayersNotFolded(GameData& gameData)
{
    auto players = gameData.getRawPlayers();
    vector<Player*> playersNotFolded;
    copy_if
    (
        players.begin(),
        players.end(),
        back_inserter(playersNotFolded),
        [] (const Player* player)
        {
            return player->getPlayerStatus() != PlayerStatus::FOLDED;
        }
    );
    return playersNotFolded;
}

bool GameUtil::isShortPlayersInHand(GameData& gameData) {
    int numInHand = 0;
    auto& players = gameData.getPlayers();
    for (const auto& player : players)
    { 
        if (player->getPlayerStatus() == PlayerStatus::IN_HAND) numInHand++;
    }
    return (numInHand < 2);
}

bool GameUtil::isActiveBetFoldedTo(GameData& gameData)
{
    auto& players = gameData.getPlayers();
    int numPlayers = players.size();
    int activeBet = 0;
    int folded = 0;

    for (const auto& player : players)
    {
        PlayerStatus status = player->getPlayerStatus();
        if (status == PlayerStatus::FOLDED) folded++;
        if (status == PlayerStatus::IN_HAND ||
            status == PlayerStatus::ALL_IN_BET) activeBet++;
    }
    return (activeBet == 1 && (folded == (numPlayers - 1)));
}

vector<pair<string, uint32_t>> GameUtil::getPlayersCurChips(GameData& gameData)
{
    vector<pair<string, uint32_t>> namesToChips;
    auto& players = gameData.getPlayers();
    for (const auto& player : players)
    {
        namesToChips.push_back
        (
            {player->getName(), player->getCurChips()}
        );
    }
    return namesToChips;
}

int GameUtil::getNumPlayersInHand(GameData& gameData)
{
    int numInHand = 0;
    auto& players = gameData.getPlayers();
    for (const auto& player : players)
    {
        if (player->getPlayerStatus() == PlayerStatus::IN_HAND) numInHand++;
    }
    return numInHand;
}

bool GameUtil::isPlayersDealt(GameData& gameData)
{
    auto& players = gameData.getPlayers();
    for (const auto& player : players)
    {
        if (player->getHand().size() != 2) return false;
    }
    return true;
}



/// NOT YET DONE

vector<string> GameUtil::getRankedNames(GameData& gameData) {
    vector<string> rankedNames;
    vector<string> rankedIds = gameData.getRankedIds();
    for (auto& id : rankedIds) {
        auto player = getPlayer(gameData, id);
        rankedNames.emplace_back(player->getName());
    }
    return rankedNames;
}

int GameUtil::getBoardSize(GameData& gameData) {
    return gameData.getBoard().getBoardSize();
}

shared_ptr<Action> GameUtil::getLastAction(GameData& gameData) {
    if (getNumActionsInTimeline(gameData) != 0) {
        return gameData.getActionTimeline().back();
    }
    return nullptr;
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