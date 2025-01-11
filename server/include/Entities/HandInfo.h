#ifndef HAND_INFO_H
#define HAND_INFO_H

#include "Card.h"
#include "../Shared/Enums.h"

#include <vector>

using HandCategory = Enums::HandCategory;

class HandInfo {
private:
    vector<Card> hand;          // Sorted vector of hand (hole and community cards)
    int handSize;               // Size of the hand
    uint64_t bitwise;           // 64 bit representation of hand
    HandCategory category;      // Category of hand (e.g. flush)
    vector<Card> bestFiveCards; // Best 5 card combination
public:
    HandInfo() : bitwise(), category(HandCategory::NONE), hand(), bestFiveCards(), handSize(0) {}

    const vector<Card>& getHand() const { return hand; }
    const vector<Card>& getBestFiveCards() const { return bestFiveCards; }
    const HandCategory getCategory() const { return category; }
    const int getHandSize() const { return handSize; }
    const uint64_t getBitwise() const { return bitwise; }

    void setHand(const vector<Card>& input) { hand = input;}
    void setHandSize(const int& size) { handSize = size; }
    void setBitwise(const uint64_t newBitwise) { bitwise = newBitwise; }
    void setCategory(const HandCategory newCategory) { category = newCategory; }
    void addToFive(const Card& card) { bestFiveCards.push_back(card); }
    void setBestFive(const vector<Card>& newFive) { bestFiveCards = newFive; }
};

#endif