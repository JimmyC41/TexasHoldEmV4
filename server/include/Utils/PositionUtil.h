#ifndef POSITION_UTIL
#define POSITION_UTIL

#include "../Shared/Enums.h"
#include "../Entities/Player.h"
#include "PrintUtil.h"
#include "GameUtil.h"
#include <memory>
#include <set>
#include <unordered_set>

using Position = Enums::Position;
using namespace std;

class PositionUtil {
public:
    static Position getPositionOfPlayer(GameData& gameData, string& idOrName);
    static Position getNextPosition(Position position);
    static Position getNextUnoccupiedPosition(unordered_set<Position> positionSet);
    static unordered_set<Position> getSetOfPositions(vector<Player*> players);
};

#endif