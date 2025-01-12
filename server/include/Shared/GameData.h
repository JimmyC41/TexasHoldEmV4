#ifndef GAME_DATA_H
#define GAME_DATA_H

#include "Enums.h"
#include "../Entities/Player.h"
#include "../Entities/Board.h"
#include "../Entities/Pot.h"

#include <string>
#include <memory>
#include <vector>
#include <algorithm>
#include <iostream>
#include <condition_variable>
#include <queue>

class Player;
class Board;
class Card;
class Action;
class PossibleAction;
class NoneAction;

using namespace std;
using Street = Enums::Street;
using Position = Enums::Position;
using PlayerStatus = Enums::PlayerStatus;

/**
 * The Game Data acts as the single source of truth for an instance of 
 * the game. Service managers push and pull to a shared Game Data that
 * is initalised by the Game Controller.
 */
class GameData {
private:
    // Shared pointers to player roles
    shared_ptr<Player> curPlayer;
    shared_ptr<Player> smallBlindPlayer;
    shared_ptr<Player> bigBlindPlayer;
    shared_ptr<Player> buttonPlayer;

    // Vector of players, sorted by position when new players are added
    vector<shared_ptr<Player>> gamePlayers;

    // Vector of IDs, ranked by hand strengths
    vector<string> rankedPlayerIds;       

    // Vector of pots, calculated at the END of each betting street
    vector<shared_ptr<Pot>> pots;

    // Vector of action objects in a given betting street
    vector<shared_ptr<Action>> actionTimeline;

    // Vector IDs to their pot amount won
    vector<pair<uint32_t, string>> winners;

    // Ptr to the last 'aggressive' action that is not CALL or FOLD
    shared_ptr<Action> activeAction;

    // Vector of Posisble Action objects for the player to act
    vector<shared_ptr<PossibleAction>> possibleActions;

    // Other game state information
    Street curStreet;
    Board board;
    uint32_t deadChips;
    uint32_t smallBlind;
    uint32_t bigBlind;

public:
    GameData() :
        curStreet(Street::NONE),
        curPlayer(),
        smallBlindPlayer(),
        bigBlindPlayer(),
        buttonPlayer(),
        gamePlayers(),
        rankedPlayerIds(),
        board(),
        pots(),
        deadChips(),
        actionTimeline(),
        activeAction(),
        smallBlind(uint32_t{1}),
        bigBlind(uint32_t{2}),
        winners()
    {}

    void reset();

    // Setter Methods
    void addPlayer(const shared_ptr<Player>& player);
    void removePlayer(const shared_ptr<Player>& player);
    void sortPlayersByPosition();
    void setLastPlayerAsButton();
    void removeAllPlayers() { gamePlayers.clear(); }
    void setRankedPlayerIds(const vector<string>& ids) { rankedPlayerIds = ids; }
    void setCurPlayer(const shared_ptr<Player>& player) { curPlayer = player; }
    void setSmallBlindPlayer(const shared_ptr<Player>& player) { smallBlindPlayer = player; }
    void setBigBlindPlayer(const shared_ptr<Player>& player) { bigBlindPlayer = player; }
    void setButtonPlayer(const shared_ptr<Player>& player) { buttonPlayer = player; }
    void setCurStreet(const Street& street) { curStreet = street; }
    void dealCommunityCard(const Card& card) { board.addCommunityCard(card); }
    void clearBoard() { board.resetBoard(); }
    void addActionToTimeline(const shared_ptr<Action>& action) { actionTimeline.push_back(action); }
    void clearActionTimeline() { actionTimeline.clear(); }
    void setActiveAction(const shared_ptr<Action>& action ) { activeAction = action; }
    void setPossibleActions(const vector<shared_ptr<PossibleAction>>& actions);
    void addNewPot(const shared_ptr<Pot>& newPot) { pots.emplace_back(newPot); }
    void addChipsToCurPot(const uint32_t& chips) { pots.back()->addChips(chips); }
    void addIdToCurPot(const string& id) { pots.back()->addPlayerId(id); }
    void addDeadChips(const uint32_t& chips) { deadChips += chips; }
    void lessDeadChips(const uint32_t& chips) { deadChips -= chips; }
    void clearAllPots() { pots.clear(); }
    void setBigBlind(const uint32_t& big) { bigBlind = big; }
    void clearPotWinners() { winners.clear(); }
    void addPotWinner(const uint32_t& chips, const string& id) { winners.emplace_back(chips, id); }

    // Getter Methods
    const shared_ptr<Player>& getCurPlayer() const { return curPlayer; }
    const shared_ptr<Player>& getSmallBlindPlayer() const { return smallBlindPlayer; }
    const shared_ptr<Player>& getBigBlindPlayer() const { return bigBlindPlayer; }
    const shared_ptr<Player>& getButtonPlayer() const { return buttonPlayer; }
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
    const uint32_t& getDeadChips() const { return deadChips; }
    const uint32_t& getBigBlind() const { return bigBlind; }
    const uint32_t& getSmallBlind() const { return smallBlind; }
    const int getNumPlayers() const { return gamePlayers.size(); }
    const vector<pair<uint32_t, string>> getPotWinners() { return winners; }
};

#endif