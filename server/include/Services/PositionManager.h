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
    // To GameData: Updates the Position attribute of the Player object and sets the buttonId
    // From GameData: Fetches vector<shared_ptr<Player>> gamePlayers
    void allocatePositions();

    // Event: Triggered at the start of the Round End state.
    // To GameData: Updates the Position attribute of all players in the gamePlayers vector
    // From GameData: Fetches gamePlayers vector
    void rotatePositions();

    // Event: Triggered at the start of the Street Setup state.
    // To GameData: Updates the curPlayerId to the first position to act.
    // From GameData: Fetches gamePlayers vector
    void setEarlyPositionToAct();

    // Event: Triggered after a client betting action is receieved in the Street In Progress state
    // To GameData: Updates curPlayerId and the isActing attribute of the Player object
    // From GameData: Fetches gamePlayers vector
    void updatePlayerToAct();
};

#endif