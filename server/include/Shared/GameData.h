#ifndef GAME_DATA_H
#define GAME_DATA_H

#include "Enums.h"
#include "Types.h"
#include "../Entities/Player.h"
#include "../Entities/Board.h"
#include "../Entities/Pot.h"

#include <string>
#include <memory>
#include <vector>
#include <algorithm>
#include <iostream>

class Player;
class Card;
class Action;
class PossibleAction;
class NoneAction;

using namespace std;
using Street = Enums::Street;
using Position = Enums::Position;

class GameData {
private:
    // Persists for the Entire Round
    // Only Persists in Each Street:
    Street curStreet;
    string curPlayerId;                         // ID of the player to act
    string smallBlindId;
    string bigBlindId;
    string buttonId;                            // ID of the player with the button
    vector<shared_ptr<Player>> gamePlayers;     // Ordered list of players by position
    vector<string> rankedPlayerIds;             // Vector of IDs ranked on hand strengths
    Board board;
    vector<shared_ptr<Pot>> pots;
    size_t deadChips;
    vector<shared_ptr<Action>> actionTimeline;  // An ordered list of actions in the current betting street
    shared_ptr<Action> activeAction;               // Ptr to the last action that is not of type CALL or FOLD
    vector<shared_ptr<PossibleAction>> possibleActions; // List of possible actions for the current player to act
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
        board(),
        pots(),
        deadChips(),
        actionTimeline(),
        activeAction(),
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
    void dealCommunityCard(const Card& card) { board.addCommunityCard(card); }
    void clearBoard() { board.resetBoard(); }
    void addActionToTimeline(const shared_ptr<Action>& action) { actionTimeline.push_back(action); }
    void clearActionTimeline() { actionTimeline.clear(); }
    void setActiveAction(const shared_ptr<Action>& action ) { activeAction = action; }
    void setPossibleActions(const vector<shared_ptr<PossibleAction>>& actions) {
        possibleActions.clear();
        for (const auto& action : actions) possibleActions.push_back(action);
    }
    void addNewPot(const shared_ptr<Pot>& newPot) { pots.emplace_back(newPot); }
    void addChipsToCurPot(const size_t& chips) { pots.back()->addChips(chips); }
    void addIdToCurPot(const string& id) { pots.back()->addPlayerId(id); }
    void addDeadChips(const size_t& chips) { deadChips += chips; }
    void lessDeadChips(const size_t& chips) { deadChips -= chips; }
    void clearAllPots() { pots.clear(); }

    // GET Methods
    const string& getSmallBlindId() const { return smallBlindId; }
    const string& getBigBlindId() const { return bigBlindId; }
    const string& getButtonId() const { return buttonId; }
    const string& getCurPlayerId() const { return curPlayerId; }
    const vector<shared_ptr<Player>>& getPlayers() { return gamePlayers; }
    const Street getStreet() const { return curStreet; }
    const Board& getBoard() const { return board; }
    const vector<Card>& getBoardCards() const { return board.getCommunityCards(); }
    const vector<string>& getRankedIds() const { return rankedPlayerIds; }
    const shared_ptr<Action>& getActiveAction() const { return activeAction; }
    const vector<shared_ptr<Action>>& getActionTimeline() const { return actionTimeline; }
    const vector<shared_ptr<PossibleAction>>& getPossibleActions() const { return possibleActions; }
    const vector<shared_ptr<Pot>>& getPots() const { return pots; }
    const shared_ptr<Pot>& getCurPot() const { return pots.back(); }
    const size_t& getDeadChips() const { return deadChips; }
};

#endif