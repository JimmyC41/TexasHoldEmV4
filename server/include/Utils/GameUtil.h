#ifndef GAME_UTIL
#define GAME_UTIL

#include "../Shared/GameData.h"

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
    static shared_ptr<Player> getPlayer(GameData& gameData, string idOrName);
    static vector<shared_ptr<Player>> getPreFlopOrderPlayers(GameData& gameData);
    static int getNumPlayers(GameData& gameData);
    static bool isPlayersDealt(GameData& gameData);
};

#endif