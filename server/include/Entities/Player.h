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
    uint32_t recentBet;

    // The number of chips the player started the street witth
    uint32_t initialChips;

public:
    Player(string name, uint32_t chips, string id);

    // Setter Methods for Player
    void addChips(uint32_t newChips);
    void setInitialChips(uint32_t chips);
    void setRecentBet(uint32_t newBet);
    void reduceChips(uint32_t lostChips);
    void setPosition(Position newPosition);
    void setPlayerStatus(PlayerStatus status);
    void addHoleCard(const Card& card);
    void clearHand();
    void setHandCategory(HandCategory category);
    void setBestFiveCards(const vector<Card>& cards);

    // Getter Methods for Player
    const string& getName() const;
    const string& getId() const;
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