#ifndef POSITION_MANAGER_H
#define POSITION_MANAGER_H

#include "../Entities/Player.h"
#include "../Shared/GameData.h"
#include "../Utils/GameUtil.h"
#include "../Utils/PositionUtil.h"

#include <set>
using namespace std;

class PositionManager {
private:
    GameData& gameData;
    set<Position> occupiedPositions; 

    /* Called in allocatePositions to determine occupied positions */
    void populateOccupiedPositions();

    /* Updates GameData when a player's position is changed */
    void updatePlayerPositionInGameData(const string& idOrName, const Position& newPosition);

    /**
     * Assigns a small and big blind if previous players
     * left the game and there are at least 2 players
     */
    void assignBlindsIfMissing();

public:
    PositionManager(GameData& gameData);

    /**
     * Called when a client request to add a player is received
     * For players, sets their position and their status to IN_HAND
     * For GameData, sorts players by position and sets the buttonId
     */
    void allocatePositions();

    /**
     * Called at the beginning of the Round End state
     * For players, rotates their positions and resets their status to IN_HAND
     */
    void rotatePositions();

    /**
     * Called at the beginning of the Street Setup state
     * Sets the early position to be the first to act
     */
    void setEarlyPositionToAct();

    /**
     * Called after a client action is receieved
     * Updates the current player to act
     */
    void updatePlayerToAct();
};

#endif