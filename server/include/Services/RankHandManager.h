#ifndef HAND_RANK_MANAGER
#define HAND_RANK_MANAGER

#include <string>
#include "../Shared/Enums.h"
#include "../Shared/Types.h"
#include "../Utils/BitwiseUtil.h"

using namespace std;
using HandInfo = Types::HandInfo;

class HandRankManager {
private:
    unordered_map<string, HandInfo> handsInfo;
public:
    // Event: Triggered at the start of the Showdown state
    // To GameState: Updates the vector<string> sortedPlayerIds
    // From GameState: Fetches the gamePlayers and access the hand attribute
    vector<string> evaluateHandsAndSortIds();
};

#endif