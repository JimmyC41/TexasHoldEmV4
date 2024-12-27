#ifndef POT_H
#define POT_H

#include <string>
#include <vector>

using namespace std;

class Pot {
private:
    size_t chips;
    vector<string> eligibleIds;

public:
    Pot() : chips(0), eligibleIds() {}
    void addPlayerId(const string& id) { eligibleIds.push_back(id); }
    void addChips(const size_t& amount) { chips += amount; }
    
    size_t getChips() const { return chips; }
    const vector<string>& getEligibleIds() const { return eligibleIds; }
    bool isIdEligible(string id) const { return find(eligibleIds.begin(), eligibleIds.end(), id) != eligibleIds.end(); }
};

#endif