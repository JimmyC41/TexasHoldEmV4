#include "../../include/Utils/PositionUtil.h"

constexpr int firstPosition = static_cast<int>(Position::SMALL_BLIND);
constexpr int lastPosition = static_cast<int>(Position::DEALER);

Position PositionUtil::getPositionOfPlayer(GameData& gameData, string& idOrName)
{
    auto player = GameUtil::getPlayer(gameData, idOrName);
    return player->getPosition();
}

Position PositionUtil::getNextPosition(Position position)
{
    int nextPosition = static_cast<int>(position) + 1;
    if (nextPosition > lastPosition) nextPosition = firstPosition;
    return static_cast<Position>(nextPosition);
}

Position PositionUtil::getNextUnoccupiedPosition(unordered_set<Position> positionSet)
{
    for (int pos = firstPosition; pos <= lastPosition; ++pos)
    {
        if (positionSet.find(static_cast<Position>(pos)) == positionSet.end())
        {
            return static_cast<Position>(pos);
        }
    }
    // Should never return LOBBY if the player has joined the game
    return Position::LOBBY;
}

unordered_set<Position> PositionUtil::getSetOfPositions(vector<Player*> players)
{
    unordered_set<Position> positions;
    for (auto& player : players)
    {
        if (player->getPosition() != Position::LOBBY)
        {
            positions.insert(player->getPosition());
        }
    }
    return positions;
}