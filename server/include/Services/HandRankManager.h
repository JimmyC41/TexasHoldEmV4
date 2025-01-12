#ifndef HAND_RANK_MANAGER
#define HAND_RANK_MANAGER

#include <string>
#include <unordered_map>
#include "../Entities/HandInfo.h"
#include "../Shared/GameData.h"
#include "../Shared/Enums.h"
#include "../Utils/BitwiseUtil.h"
#include "../Utils/HandRankUtil.h"
#include "../Utils/GameUtil.h"
#include "../Utils/PlayerUtil.h"

using namespace std;

class HandRankManager {
private:
    GameData& gameData;
    unordered_map<string, HandInfo> handsInfo;

    // For players in the GameData, gather and record information about their hand.
    void populateHandsInfo(GameData& gameData);

    // Returns true if handA is stronger than handB
    bool compareHands(const HandInfo& handA, const HandInfo& handB);
    
public:
    HandRankManager(GameData& gameData) : gameData(gameData), handsInfo() {}

    /**
     * Called at the start of the showdown state
     * Evaluates hand rankings and pushes player rankings to the Game Data
     */
    void evaluateRankedIds();
};

#endif