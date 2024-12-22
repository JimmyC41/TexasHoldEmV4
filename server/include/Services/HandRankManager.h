#ifndef HAND_RANK_MANAGER
#define HAND_RANK_MANAGER

#include <string>
#include <unordered_map>
#include "../Shared/GameData.h"
#include "../Shared/Enums.h"
#include "../Shared/Types.h"
#include "../Utils/BitwiseUtil.h"
#include "../Utils/HandRankUtil.h"
#include "../Utils/GameUtil.h"
#include "../Utils/PlayerUtil.h"

using namespace std;
using HandInfo = Types::HandInfo;

class HandRankManager {
private:
    GameData& gameData;
    unordered_map<string, HandInfo> handsInfo;

    // For players in the GameData, gather and record information about their hand.
    void populateHandsInfo(GameData& gameData);

    bool compareHands(const HandInfo& handA, const HandInfo& handB);
public:
    HandRankManager(GameData& gameData) : gameData(gameData), handsInfo() {}

    // Event: Triggered at the start of the Showdown state
    // To GameState: Updates the vector<string> rankedPlayerIds
    // From GameState: Fetches the gamePlayers and access the hand attribute
    void evaluateRankedIds(GameData& gameData);
};

#endif