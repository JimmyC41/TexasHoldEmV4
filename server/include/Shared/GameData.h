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
#include <unordered_map>

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

class GameData {
private:
    // Persists for the Entire Round
    Player* curPlayer;
    Player* smallBlindPlayer;
    Player* bigBlindPlayer;
    Player* buttonPlayer;

    vector<unique_ptr<Player>> gamePlayers;     // Ordered list of players by position
    vector<string> rankedPlayerIds;             // Vector of IDs ranked on hand strengths (calculated in the Winner game state)
    vector<shared_ptr<Pot>> pots;               // Calculated at the end of each betting street
    uint32_t deadChips;
    Board board;
    uint32_t smallBlind;
    uint32_t bigBlind;
    vector<pair<uint32_t, string>> winners;

    // Only Persists in Each Street:
    Street curStreet;
    vector<shared_ptr<Action>> actionTimeline;              // An ordered list of actions in the current betting street
    shared_ptr<Action> activeAction;                        // Ptr to the last action that is not of type CALL or FOLD
    vector<shared_ptr<PossibleAction>> possibleActions;     // List of possible actions for the current player to act

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

    // SETTER Methods for Players
    void addPlayer(unique_ptr<Player> player);  // Ownership is transferred from Player Manager
    void removePlayer(Player* player);
    void sortPlayersByPosition();
    void setLastPlayerAsButton();
    void setCurPlayer(Player* player);
    void setSmallBlindPlayer(Player* player);
    void setBigBlindPlayer(Player* player);
    void setButtonPlayer(Player* player);
    void removeAllPlayers();


    void setRankedPlayerIds(const vector<string>& ids) { rankedPlayerIds = ids; }
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
    void addChipsToCurPot(const uint32_t& chips) { pots.back()->addChips(chips); }
    void addIdToCurPot(const string& id) { pots.back()->addPlayerId(id); }
    void addDeadChips(const uint32_t& chips) { deadChips += chips; }
    void lessDeadChips(const uint32_t& chips) { deadChips -= chips; }
    void clearAllPots() { pots.clear(); }
    void setBigBlind(const uint32_t& big) { bigBlind = big; }
    void clearPotWinners() { winners.clear(); }
    void addPotWinner(const uint32_t& chips, const string& id) { winners.emplace_back(chips, id); }

    // GETTER Methods for Players
    Player* getCurPlayer();
    Player* getSmallBlindPlayer();
    Player* getBigBlindPlayer();
    Player* getButtonPlayer();
    const vector<unique_ptr<Player>>& getPlayers() const;
    vector<Player*> getRawPlayers() const;
    int getNumPlayers() const;

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
    const vector<pair<uint32_t, string>> getPotWinners() { return winners; }
};

#endif