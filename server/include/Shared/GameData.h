#ifndef GAME_DATA_H
#define GAME_DATA_H

#include "Enums.h"
#include "Types.h"
#include "../Entities/Player.h"
#include <string>
#include <memory>

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
    vector<string> sortedPlayerIds;             // Vector of IDs ranked on hand strengths
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
        sortedPlayerIds(),
        communityCards(),
        pots(),
        deadChips(),
        actionTimeline(),
        lastBetAction(),
        activeBet(),
        smallBlind(),
        bigBlind()
    {}

    // Setter Methods
    void addPlayer(shared_ptr<Player> player);
    void setPlayerPosition(string id, Position position);

    // Getter Methods that DO NOT modify the game state
    shared_ptr<Player> getPlayer(string idOrName) const;
    const string& getBigBlindId() const { return bigBlindId;}
    vector<shared_ptr<Player>> getPreFlopOrderPlayers();

    // Getter Methods that DO modify the game state
    const vector<shared_ptr<Player>>& getPlayers() { return gamePlayers; }

    // Test Helper Methods
    int getNumPlayers() const;
    bool isPlayersDealt() const;
};

#endif