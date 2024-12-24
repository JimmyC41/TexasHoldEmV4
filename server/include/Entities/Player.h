#ifndef PLAYER_H
#define PLAYER_H

#include "Card.h"
#include "Action.h"
#include "../Shared/Enums.h"
#include "../Utils/PlayerUtil.h"

#include <vector>
#include <string>
#include <iostream>

using namespace std;
using Position = Enums::Position;
using PlayerStatus = Enums::PlayerStatus;

class Player {
private:
    string name;
    string id;
    Position position;
    size_t curChips;
    vector<Card> hand;
    HandCategory handCategory;
    vector<Card> bestFiveCards;
    PlayerStatus playerStatus;
    bool isActing;
    size_t initialChips; // Chips the player started the street with
    vector<shared_ptr<Action>> possibleActions;
    size_t recentBet;
public:
    Player(string name, size_t chips);

    void setPosition(Position newPosition);
    void addChips(size_t newChips);
    void reduceChips(size_t lostChips);
    void addHoleCard(const Card& card);
    void clearHand();
    void setPlayerStatus(PlayerStatus status);
    void setIsActing(bool act);
    void setInitialChips(size_t chips);
    void setPossibleActions(const vector<shared_ptr<Action>>& actions);
    void setRecentBet(size_t newBet);
    void setHandCategory(HandCategory category);
    void setBestFiveCards(vector<Card>& cards);

    const string& getId() const;
    const string& getName() const;
    Position getPosition() const;
    size_t getCurChips() const;
    const vector<Card>& getHand() const;
    const vector<Card>& getBestFiveCards() const;
    PlayerStatus getPlayerStatus() const;
    bool getIsActing() const;
    size_t getInitialChips() const;
    const vector<shared_ptr<Action>>& getPossibleActions() const;
    size_t getRecentBet() const;
    HandCategory getHandCategory() const;
};

#endif