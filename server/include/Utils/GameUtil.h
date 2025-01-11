#ifndef GAME_UTIL
#define GAME_UTIL

#include "../Shared/GameData.h"
#include "../Shared/Enums.h"
#include "PrintUtil.h"

using PlayerStatus = Enums::PlayerStatus;

class GameUtil {
public:
    // Returns an iterator if a player with the given id or name exists
    static vector<unique_ptr<Player>>::const_iterator findPlayerIt(GameData& gameData, string idOrName);

    // SETTER Helper Methods for Players
    static void clearPlayerHands(GameData& gameData);
    static void setPlayerInitialToCurChips(GameData& gameData);
    static void resetPlayerRecentBets(GameData& gameData);
    static void setInHandStatusForPlayers(GameData& gameData);

    // GETTER Helper Methods for Players
    static Player* getPlayer(GameData& gameData, const string& idOrName);
    static int getNumPlayers(GameData& gameData);
    static vector<string> getPlayerIds(GameData& gameData);
    static vector<string> getPlayerNames(GameData& gameData);
    static vector<string> getListofNames(GameData& gameData);
    static vector<Position> getListOfPositions(GameData& gameData);
    static string getPlayerNameFromId(GameData& gameData, string id);
    static vector<string> getNamesFromIds(GameData& gameData, const vector<string>& ids);
    static string getCurPlayerId(GameData& gameData);
    static string getCurPlayerName(GameData& gameData);
    static bool isSmallBlindExists(GameData& gameData);
    static bool isBigBlindExists(GameData& gameData);
    static bool isPlayerBigBlind(GameData& gameData, string idOrName);
    static bool isPlayerExists(GameData& gameData, string idOrName);
    static HandCategory getPlayerHandCategory(GameData& gameData, string idOrName);
    static vector<Card> getPlayerBestFiveCards(GameData& gameData, string idOrName);
    static uint32_t getPlayerInitialChips(GameData& gameData, string idOrName);
    static uint32_t getBigStackAmongOthers(GameData& gameData);
    static Player* getEarlyPosition(GameData& gameData);
    static Player* getNextPlayerInHand(GameData& gameData, string idOrName);
    static vector<Player*> getOccupiedPlayers(GameData& gameData);
    static vector<Player*> getPlayersNotFolded(GameData& gameData);
    static bool isShortPlayersInHand(GameData& gameData);
    static bool isActiveBetFoldedTo(GameData& gameData);
    static vector<pair<string, uint32_t>> getPlayersCurChips(GameData& gameData);
    static int getNumPlayersInHand(GameData& gameData);
    static bool isPlayersDealt(GameData& gameData);

    // NOT TOUCHED YET
    static vector<string> getRankedNames(GameData& gameData);
    static int getBoardSize(GameData& gameData);
    static shared_ptr<Action> getLastAction(GameData& gameData);
    static int getNumActionsInTimeline(GameData& gameData);
    static ActionType getActiveActionType(GameData& gameData);
    static uint32_t getActiveActionAmount(GameData& gameData);
    static bool isIdInCurPot(GameData& gameData, string id);
    static uint32_t getNumPots(GameData& gameData);
    static bool isAPossibleAction(GameData& gameData, ActionType type, const uint32_t& amount);
};

#endif