#ifndef TYPES_H
#define TYPES_H

#include <cstddef>
#include <string>
using namespace std;

namespace Types {

// Structure of an individual pot
// Game has one main pot, and additional side pots
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

}

#endif