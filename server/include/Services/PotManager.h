#ifndef POT_MANAGER_H
#define POT_MANAGER_H

#include "../Entities/Player.h"
#include "../Entities/Pot.h"
#include "../Utils/PotUtil.h"
#include "../Utils/PrintUtil.h"

using namespace std;
using PlayerBetInfo = vector<tuple<string, uint32_t, PlayerStatus>>;


class PotManager {
private:
    GameData& gameData;

    /**
     * Player Bets Info is 'cleared' after each Street when all bets
     * have been moved to Pots BUT is repopulated at the start
     *  of each streets as further bets need to be processed
     */
    PlayerBetInfo playerBets;

    /* Records each player's bet and status from Game Data */
    void populatePlayerBets(); 

    /**
     * Fetches the minimum bet in player bets, i.e. the minimum
     * contribution each player makes to the current pot
     */
    uint32_t getMinBetInPlayerBets();

    /**
     * Checks if all player bets have been allocated to pots
     * If there are remaining bets to be processed, then there are side-pots to handle!
     */
    bool allBetsAllocatedToPots();

public:
    PotManager(GameData& gameData);

    /**
     * Called at the beginning of the Street End state
     * Calculates pots, dead chips and sets all recent bets to 0
     */
    void calculatePots();

    /**
     *  Triggered at the beginning of the Winner state
     * Awards chips to players according to their hand ranking and pot eligibility
     */
    void awardPots();
};

#endif