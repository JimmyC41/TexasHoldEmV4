#ifndef POT_H
#define POT_H

#include <string>
#include <vector>

using namespace std;

class Pot {
private:
    uint32_t chips;
    vector<string> contributorIds;

public:
    Pot() : chips(0), contributorIds() {}
    void addPlayerId(const string& id) { contributorIds.push_back(id); }
    void addChips(const uint32_t& amount) { chips += amount; }
    
    uint32_t getChips() const { return chips; }
    const vector<string>& getContributorIds() const { return contributorIds; }
    bool isIdAContributor(const string& id) const
    {
        return (std::find(contributorIds.begin(), contributorIds.end(), id) != contributorIds.end());
    }
};

#endif