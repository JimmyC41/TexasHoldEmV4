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
    
    void displayGameStateStdOut();
    void displayPossibleActionsStdOut();

    vector<pair<string, size_t>> addPlayersStdIn();
    vector<string> removePlayersStdIn();
    pair<ActionType, size_t> getPlayerActionStdIn();
};

#endif