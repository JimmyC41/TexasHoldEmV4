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

    // Player Bets Info is 'cleared' after each Street
    // when all bets have been moved to Pots
    // BUT is repopulated at the start of each street as
    // further bets need to be processed
    PlayerBetInfo playerBets;

    // Records each player's bet and status from Game Data
    void populatePlayerBets(); 

    // Fetches the minimum bet in player bets, the minimum
    // contribution each player makes to the current pot
    uint32_t getMinBetInPlayerBets();

    // Checks if all player bets have been allocated to pots
    // If there are remaining bets to be processed, then there
    // are side-pots to handle!
    bool allBetsAllocatedToPots();
public:
    PotManager(GameData& gameData);
    
    // Event: Triggered at the start of Street End state
    // To GameData: Calculates pots, dead chips and sets all recent bets to 0
    void calculatePots();

    // Event: Triggered at the start of the Announce Winner state
    // To: Awards chips to players according to their hand ranking
    // and pot eligibility
    void awardPots();
};

#endif // POT_MANAGER_H