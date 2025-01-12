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
using HandCategory = Enums::HandCategory;

class Player {
private:
    string name;
    string id;
    Position position;
    uint32_t curChips;
    vector<Card> hand;
    HandCategory handCategory;
    vector<Card> bestFiveCards;
    PlayerStatus playerStatus;
    uint32_t initialChips; // Chips the player started the street with
    uint32_t recentBet;

public:
    Player(string name, uint32_t chips, string id);

    void setPosition(Position newPosition);
    void addChips(uint32_t newChips);
    void reduceChips(uint32_t lostChips);
    void addHoleCard(const Card& card);
    void clearHand();
    void setPlayerStatus(PlayerStatus status);
    void setInitialChips(uint32_t chips);
    void setRecentBet(uint32_t newBet);
    void setHandCategory(HandCategory category);
    void setBestFiveCards(const vector<Card>& cards);

    const string& getId() const;
    const string& getName() const;
    Position getPosition() const;
    uint32_t getCurChips() const;
    const vector<Card>& getHand() const;
    const vector<Card>& getBestFiveCards() const;
    PlayerStatus getPlayerStatus() const;
    uint32_t getInitialChips() const;
    uint32_t getRecentBet() const;
    HandCategory getHandCategory() const;
};

#endif