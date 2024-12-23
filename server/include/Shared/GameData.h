#ifndef GAME_DATA_H
#define GAME_DATA_H

#include "Enums.h"
#include "Types.h"
#include "../Entities/Player.h"
#include <string>
#include <memory>
#include <vector>
#include <algorithm>

class Player;
class Card;
class Action;

using namespace std;
using Street = Enums::Street;
using Pot = Types::Pot;
using Position = Enums::Position;

class GameData {
private:
    Street curStreet;
    string curPlayerId;                         // ID of the player to act
    string smallBlindId;
    string bigBlindId;
    string buttonId;                            // ID of the player with the button
    vector<shared_ptr<Player>> gamePlayers;     // Ordered list of players by position
    vector<string> rankedPlayerIds;             // Vector of IDs ranked on hand strengths
    vector<shared_ptr<Card>> communityCards;
    vector<shared_ptr<Pot>> pots;
    size_t deadChips;
    vector<shared_ptr<Action>> actionTimeline;  // An ordered list of actions in the current betting street
    shared_ptr<Action> lastBetAction;           // Ptr to the last action that is not of type CALL or FOLD
    size_t activeBet;                           // The current bet amount to match
    size_t smallBlind;
    size_t bigBlind;
public:
    GameData() : 
        curStreet(Street::NONE),
        smallBlindId(),
        bigBlindId(),
        curPlayerId(),
        buttonId(),
        gamePlayers(),
        rankedPlayerIds(),
        communityCards(),
        pots(),
        deadChips(),
        actionTimeline(),
        lastBetAction(),
        activeBet(),
        smallBlind(),
        bigBlind()
    {}

    // SET Methods
    void addPlayer(const shared_ptr<Player>& player);
    bool removePlayer(const shared_ptr<Player>& player);
    void sortPlayersByPosition();
    void setLastPlayerAsButton();

    void removeAllPlayers() { gamePlayers.clear(); }
    void setRankedPlayerIds(const vector<string>& ids) { rankedPlayerIds = ids; }
    void setSmallBlindId(const string& id) { smallBlindId = id; }
    void setBigBlindId(const string& id) { bigBlindId = id; }
    void setCurPlayerId(const string&id) { curPlayerId = id; }
    void setCurStreet(const Street& street) { curStreet = street; }

    // GET Methods
    const string& getSmallBlindId() const { return smallBlindId; }
    const string& getBigBlindId() const { return bigBlindId; }
    const string& getButtonId() const { return buttonId; }
    const string& getCurPlayerId() const { return curPlayerId; }
    const vector<shared_ptr<Player>>& getPlayers() { return gamePlayers; }
    const Street getStreet() const { return curStreet; }
};

#endif