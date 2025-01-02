#ifndef PLAYER_UTIL
#define PLAYER_UTIL

#include "../Entities/Player.h"
#include <string>
#include <memory>
using namespace std;

class Player;

class PlayerUtil {
public:
    static string generateUUID();
    static vector<string> playerPointersToIds(vector<shared_ptr<Player>>& players);
    static bool isValidName(const string& name);
    static bool isMinBuyin(size_t bigBlind, const uint32_t& chips);
};

#endif