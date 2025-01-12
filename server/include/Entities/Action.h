#ifndef ACTION_H
#define ACTION_H

#include "../Shared/Enums.h"
#include <string>

using namespace std;
using ActionType = Enums::ActionType;

class Action {
private:
    string playerId;
    uint32_t betAmount;

public:
    Action(string id, uint32_t amount = 0) : playerId(id), betAmount(amount) {}
    const string& getPlayerId() { return playerId; }
    const uint32_t& getAmount() { return betAmount; }
    
    virtual ~Action() {}
    virtual ActionType getActionType() const = 0;
};

#endif