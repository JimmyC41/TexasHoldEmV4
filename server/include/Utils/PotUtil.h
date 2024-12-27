#ifndef POT_UTIL_H
#define POT_UTIL_H

#include "Shared/Enums.h"
#include "Shared/GameData.h"

#include <vector>
#include <string>

using namespace std;
using PlayerStatus = Enums::PlayerStatus;

using PlayerBetInfo = vector<tuple<string, size_t, PlayerStatus>>;

class PotUtil { 
private:
public:
    static PlayerBetInfo getPlayerRecentBets(GameData& gameData);
};

#endif