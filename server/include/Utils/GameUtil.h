#ifndef GAME_UTIL
#define GAME_UTIL

#include "../Shared/GameData.h"
#include "../Shared/Enums.h"
#include "PrintUtil.h"
#include <algorithm>

using PlayerStatus = Enums::PlayerStatus;

class GameUtil {
public:
    // Returns an iterator if a player with the given id or name exists
    static vector<shared_ptr<Player>>::const_iterator findPlayerIt(GameData& gameData, string idOrName);

    // SET Methods
    static void setPlayerPosition(GameData& gameData, string id, Position position);
    static void clearPlayerHands(GameData& gameData);
    static void removePlayer(GameData& gameData, string idOrName);
    static void setPlayerInitialToCurChips(GameData& gameData);
    static void resetPlayerRecentBets(GameData& gameData);
    static void setInHandStatusForPlayers(GameData& gameData);

    // GET Methods
    static vector<string> getPlayerIds(GameData& gameData);
    static vector<string> getPlayerNames(GameData& gameData);
    static vector<string> getListofNames(GameData& gameData);
    static vector<string> getNamesFromIds(GameData& gameData, const vector<string>& ids);
    static vector<Position> getListOfPositions(GameData& gameData);
    static string getPlayerNameFromId(GameData& gameData, string id);
    static shared_ptr<Player> getPlayer(GameData& gameData, string idOrName);
    static bool isPlayerBigBlind(GameData& gameData, string idOrName);
    static bool isSmallBlindExists(GameData& gameData);
    static bool isBigBlindExists(GameData& gameData);
    static bool isPlayerExists(GameData& gameData, string idOrName);
    static HandCategory getPlayerHandCategory(GameData& gameData, string idOrName);
    static vector<Card> getPlayerBestFiveCards(GameData& gameData, string idOrName);
    static size_t getPlayerInitialChips(GameData& gameData, string idOrName);
    static size_t getBigStackAmongOthers(GameData& gameData, string idOrName);
    static vector<string> getRankedNames(GameData& gameData);
    static shared_ptr<Player> getEarlyPosition(GameData& gameData);
    static shared_ptr<Player> getNextPlayerInHand(GameData& gameData, string idOrName);
    static vector<shared_ptr<Player>> getPreFlopOrderPlayers(GameData& gameData);
    static vector<shared_ptr<Player>> getOccupiedPlayers(GameData& gameData);
    static vector<pair<string, size_t>> getPlayersCurChips(GameData& gameData);
    static int getNumPlayers(GameData& gameData);
    static int getNumPlayersInHand(GameData& gameData);
    static bool isPlayersDealt(GameData& gameData);
    static int getBoardSize(GameData& gameData);
    static int getNumActionsInTimeline(GameData& gameData);
    static ActionType getActiveActionType(GameData& gameData);
    static size_t getActiveActionAmount(GameData& gameData);
    static bool isIdInCurPot(GameData& gameData, string id);
    static size_t getNumPots(GameData& gameData);
    static bool isShortPlayersInHand(GameData& gameData);
    static bool isActiveBetFoldedTo(GameData& gameData);
};

#endif