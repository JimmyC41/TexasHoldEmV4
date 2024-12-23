#ifndef TYPES_H
#define TYPES_H

#include "Enums.h"
#include "../Entities/Card.h"
#include <cstddef>
#include <string>
#include <vector>

class Card;

using namespace std;
using HandCategory = Enums::HandCategory;

namespace Types {

typedef struct Pot {
    size_t chips;
    vector<string> eligibleIds;

    Pot() : chips(0), eligibleIds() {}

    void addPlayerId(string id) { eligibleIds.push_back(id); }

    void addChips(size_t amount) { chips += amount; }

    size_t getChips() const { return chips; }

    vector<string> getEligibleIds() const { return eligibleIds; }

    bool isIdEligible(string id) const { return find(eligibleIds.begin(), eligibleIds.end(), id) != eligibleIds.end(); }
} Pot;


// Ranking information about a hand
typedef struct HandInfo {
    HandInfo() : bitwise(), category(HandCategory::NONE), hand(), bestFiveCards(), handSize(0) {}

    vector<Card> hand;          // Sorted vector of hand (hole and community cards)
    int handSize;               // Size of the hand
    uint64_t bitwise;           // 64 bit representation of hand
    HandCategory category;      // Category of hand (e.g. flush)
    vector<Card> bestFiveCards; // Best 5 card combination
} HandInfo;
}

#endif