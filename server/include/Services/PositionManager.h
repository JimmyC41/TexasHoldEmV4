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

    // Called in allocatePositions to determine occupied positions
    void populateOccupiedPositions();

    // Updates GameData when a player's position is changed
    void updatePlayerPositionInGameData(const string& idOrName, const Position& newPosition);

public:
    PositionManager(GameData& gameData);

    // Event: Triggered when a client request to add a player is received in the Game Setup state
    // To GameData:
    // For players, sets their position and their status to IN_HAND
    // For GameData, sorts players by position and sets the buttonId
    void allocatePositions();

    // Event: Triggered at the start of the Round End state.
    // To GameData:
    // For players, rotates their positions and resets their status to IN_HAND
    void rotatePositions();

    // Event: Triggered at the start of the Street Setup state.
    // To GameData:
    // Updates the curPlayerId to the first position to act
    void setEarlyPositionToAct();

    // Event: Triggered after a client betting action is receieved in the Street In Progress state
    // To GameData:
    // Updates the curPlayerId to the next player to act in the game
    void updatePlayerToAct();
};

#endif