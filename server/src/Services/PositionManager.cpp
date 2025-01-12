#include "../../include/Services/PositionManager.h"

// Rule: Any time a player(s) position is changed:
// The position is updated in the player instance
// populateOccupiedPositions is called to update thet set of occupied positions

PositionManager::PositionManager(GameData& gameData) :
    gameData(gameData),
    occupiedPositions() {}

void PositionManager::populateOccupiedPositions() {
    occupiedPositions.clear();

    occupiedPositions = PositionUtil::getSetOfPositions(
            GameUtil::getOccupiedPlayers(gameData)
    );
}

void PositionManager::updatePlayerPositionInGameData(const string& idOrName, const Position& newPosition) {
    auto player = GameUtil::getPlayer(gameData, idOrName);

    player->setPosition(newPosition);
    if (newPosition == Position::SMALL_BLIND) {
        gameData.setSmallBlindPlayer(player);
    }
    if (newPosition == Position::BIG_BLIND) {
        gameData.setBigBlindPlayer(player);
    }
}

void PositionManager::allocatePositions() {
    // Populate the set of occupied positions from the player vector
    // Occupied positions before allocating position to a new player informs us
    // where we can NOT place new players
    populateOccupiedPositions();

    // Allocate position for each player
    auto& players = gameData.getPlayers();
    for (auto& player : players) {
        // Ignore existing players, we are only trying to allocate positions for new players
        if (player->getPosition() != Position::LOBBY) continue;

        // Fetch the next unoccupied position and add this to the occupied set
        // We can't allocate this position to another player
        Position nextPos = PositionUtil::getNextUnoccupiedPosition(occupiedPositions);
        occupiedPositions.insert(nextPos);

        // Set the player's position and update GameData
        updatePlayerPositionInGameData(player->getId(), nextPos);
    }

    // Sort the gamePlayers vector by position and set the button
    gameData.sortPlayersByPosition();
    gameData.setLastPlayerAsButton();

    // Set players' status to IN_HAND
    GameUtil::setInHandStatusForPlayers(gameData);

    // Assign small and big blinds if players have left the game
    assignBlindsIfMissing();
}

void PositionManager::rotatePositions() {
    // Fetch the previous button and small blind
    string newSmallId = gameData.getButtonPlayer()->getId();
    string newBigId = gameData.getSmallBlindPlayer()->getId();

    // Button becomes new small, small becomes new big
    updatePlayerPositionInGameData(newSmallId, Position::SMALL_BLIND);
    updatePlayerPositionInGameData(newBigId, Position::BIG_BLIND);

    // From the BB onwards, update their position!
    auto& players = gameData.getPlayers();
    for (auto& player : players) {
        // Ignore the new small and big blinds - their positions have already been updated!
        if (player->getId() == newSmallId || player->getId() == newBigId) continue;

        Position newPosition = PositionUtil::getNextPosition(player->getPosition());
        updatePlayerPositionInGameData(player->getId(), newPosition);
    }

    // Sort the gamePlayes vector by position and set the button
    gameData.sortPlayersByPosition();
    gameData.setLastPlayerAsButton();

    // Set players' status to IN_HAND for the next round
    GameUtil::setInHandStatusForPlayers(gameData);
}

void PositionManager::updatePlayerToAct() {
    // Find the player the next player to act
    const string& curId = gameData.getCurPlayer()->getId();
    shared_ptr<Player> nextPlayer = GameUtil::getNextPlayerInHand(gameData, curId);

    // Set the next player as the next to act
    if (nextPlayer != nullptr) {
        gameData.setCurPlayer(nextPlayer);
    }
}

void PositionManager::setEarlyPositionToAct() {
    Street curStreet = gameData.getStreet();
    shared_ptr<Player> earlyPosition;

    // If Preflop, then early position is the player after the BB
    // For all other streets, early position is the SB
    switch(curStreet) {
        case Street::PRE_FLOP:
            earlyPosition = GameUtil::getNextPlayerInHand(gameData,
                    gameData.getBigBlindPlayer()->getId());
            break;
        default:
            earlyPosition = GameUtil::getEarlyPosition(gameData); 
            break;
    }

    // Set the current player to act
    gameData.setCurPlayer(earlyPosition);
}

void PositionManager::assignBlindsIfMissing() {
    if (GameUtil::getNumPlayers(gameData) < 2) return;

    bool smallExists = GameUtil::isSmallBlindExists(gameData);
    bool bigExists = GameUtil::isBigBlindExists(gameData);

    // Either previous small and big blinds have left the game
    if (!smallExists || !bigExists) {
        auto players = gameData.getPlayers();
        updatePlayerPositionInGameData(players[0]->getId(), Position::SMALL_BLIND);
        updatePlayerPositionInGameData(players[1]->getId(), Position::BIG_BLIND);
    }
}