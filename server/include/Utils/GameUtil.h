#ifndef GAME_UTIL
#define GAME_UTIL

#include "../Shared/GameData.h"
#include "PrintUtil.h"
#include <algorithm>

class GameUtil {
public:
    // Returns an iterator if a player with the given id or name exists
    static vector<shared_ptr<Player>>::const_iterator findPlayerIt(GameData& gameData, string idOrName);

    // SET Methods
    static void setPlayerPosition(GameData& gameData, string id, Position position);
    static void clearPlayerHands(GameData& gameData);
    static void removePlayer(GameData& gameData, string idOrName);

    // GET Methods
    static vector<string> getPlayerIds(GameData& gameData);
    static vector<string> getListofNames(GameData& gameData);
    static vector<Position> getListOfPositions(GameData& gameData);
    static string getPlayerNameFromId(GameData& gameData, string id);
    static shared_ptr<Player> getPlayer(GameData& gameData, string idOrName);
    static shared_ptr<Player> getEarlyPosition(GameData& gameData);
    static shared_ptr<Player> getNextPlayer(GameData& gameData, string idOrName);
    static vector<shared_ptr<Player>> getPreFlopOrderPlayers(GameData& gameData);
    static vector<shared_ptr<Player>> getOccupiedPlayers(GameData& gameData);
    static int getNumPlayers(GameData& gameData);
    static bool isPlayersDealt(GameData& gameData);
};

#endif