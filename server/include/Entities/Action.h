#ifndef ACTION_H
#define ACTION_H

#include "../Shared/Enums.h"
#include <string>

using namespace std;
using ActionType = Enums::ActionType;

class Action {
private:
    string playerId;
    size_t betAmount;

public:
    Action(string id, size_t amount = 0) : playerId(id), betAmount(amount) {}

    const string& getPlayerId() { return playerId; }
    const size_t& getAmount() { return betAmount; }
    
    virtual ~Action() {}
    virtual ActionType getActionType() const = 0;
};

#endif