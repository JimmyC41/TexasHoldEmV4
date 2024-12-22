#ifndef PLAYER_UTIL
#define PLAYER_UTIL

#include "../Shared/GameData.h"
#include "../Entities/Player.h"
#include <uuid/uuid.h>
#include <string>
#include <memory>
using namespace std;

class PlayerUtil {
public:
    static string generateUUID();
    static vector<string>& playerPointersToIds(vector<shared_ptr<Player>>& players);
};

#endif