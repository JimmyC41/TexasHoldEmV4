#ifndef GAME_DATA_H
#define GAME_DATA_H

#include "Enums.h"
#include "Types.h"
#include "../Entities/Player.h"
#include <string>
#include <memory>
#include <vector>

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
    void setRankedPlayerIds(const vector<string>& ids);
    void setBigBlindId(const string& id);

    // GET Methods
    const string& getBigBlindId() const { return bigBlindId; }
    const vector<shared_ptr<Player>>& getPlayers();
};

#endif