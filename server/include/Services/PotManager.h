#ifndef POT_MANAGER_H
#define POT_MANAGER_H

#include "../Entities/Player.h"
#include "../Shared/Types.h"

#include <set>
#include <map>

using namespace std;
using Pot = Types::Pot;

class PotManager {
private:
    void newPot();
    Pot& getCurPot();

public:
    PotManager();
    
    // Event: Triggered at the start of Street End state
    // To GameData: Updates vector<Pot> pots
    // From GameData: Fetches recent bets for each player in the hand
    void calculatePots();

    // Event: Triggered at the start of the Announce Winner state
    // To: Awards chips to winners
    // GameData: Fetches the ranking of players' by hand strength
    void awardPots();

    // Event: Triggered at the start of Round End State
    // To GameData: Clears the vector<Pot> pots
    void resetPots();
};

#endif // POT_MANAGER_H