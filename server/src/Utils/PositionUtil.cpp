#include "../../include/Utils/PositionUtil.h"

Position PositionUtil::getPositionOfPlayer(GameData& gameData, string& idOrName) {
    auto player = GameUtil::getPlayer(gameData, idOrName);
    return player->getPosition();
}

Position PositionUtil::getNextPosition(Position position) {
    int nextPosition = static_cast<int>(position) + 1;
    if (nextPosition > lastPosition) nextPosition = firstPosition;

    return static_cast<Position>(nextPosition);
}

Position PositionUtil::getNextUnoccupiedPosition(set<Position> positionSet) {
    for (int pos = firstPosition; pos <= lastPosition; ++pos) {
        if (positionSet.find(static_cast<Position>(pos)) == positionSet.end()) {
            return static_cast<Position>(pos);
        }
    }
    return Position::LOBBY; // Should never return LOBBY
}

set<Position> PositionUtil::getSetOfPositions(vector<shared_ptr<Player>> players) {
    set<Position> positions;
    for (auto& player : players) {
        if (player->getPosition() != Position::LOBBY) {
            positions.insert(player->getPosition());
        }
    }
    return positions;
}