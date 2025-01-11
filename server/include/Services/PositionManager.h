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
    unordered_set<Position> occupiedPositions; 

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
     * Provided the players vector is populated:
     * 1) Allocates new players with a position
     * 2) Sorts players by their position
     * 3) Sets blinds and button
     * Result: After this, we can begin the Poker Round
     * Called every time a player is added to the game.
     */
    void allocatePositions();

    /**
     * Rotates players and resets their player status.
     * Called at the end of the Winner state.
     */
    void rotatePositions();

    /**
     * Updates the current player Id to the first position to act.
     * Called at the start of each Betting Street.
     */
    void setEarlyPositionToAct();

    /**
     * Moves the current player to the next immediate player.
     * Called after a betting action is processed.
     */
    void updatePlayerToAct();
};

#endif