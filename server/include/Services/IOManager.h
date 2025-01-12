#ifndef IO_MANAGER_H
#define IO_MANAGER_H

#include "../Shared/Enums.h"
#include "../Shared/GameData.h"
#include "../Utils/PrintUtil.h"
#include "../Utils/IOUtil.h"

#include <vector>
#include <string>

using ActionType = Enums::ActionType;
using namespace std;

class IOManager {
private:
    GameData& gameData;

public:
    IOManager(GameData& gameData);
    
    // cout Methods
    void displayPlayers();
    void displayGameStateStdOut();
    void displayPossibleActionsStdOut();
    void displayActionTimeline();
    void displaySubscribers();

    // Test Helper Methods
    vector<pair<string, uint32_t>> addPlayersStdIn();
    vector<string> removePlayersStdIn();
    pair<ActionType, uint32_t> getPlayerActionStdIn();
};

#endif