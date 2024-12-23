#ifndef POSITION_UTIL
#define POSITION_UTIL

#include "../Shared/Enums.h"
#include "PrintUtil.h"
#include "GameUtil.h"
#include "../Entities/Player.h"
#include <memory>
#include <set>

using namespace std;
using Position = Enums::Position;

constexpr int firstPosition = static_cast<int>(Position::SMALL_BLIND);
constexpr int lastPosition = static_cast<int>(Position::DEALER);

class PositionUtil {
public:
    static Position getPositionOfPlayer(GameData& gameData, string& idOrName);
    static Position getNextPosition(Position position);
    static Position getNextUnoccupiedPosition(set<Position> positionSet);
    static set<Position> getSetOfPositions(vector<shared_ptr<Player>> players);
};

#endif