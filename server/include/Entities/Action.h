#ifndef ACTION_H
#define ACTION_H

#include "../Shared/Enums.h"
#include <string>

using namespace std;
using ActionType = Enums::ActionType;

class Action {
private:
    string playerId;

public:
    Action(string id) : playerId(id) {}

    string getPlayerId() { return playerId; }
    
    virtual ~Action() {}
    virtual ActionType getActionType() const = 0;
    virtual size_t getAmount() const = 0;
};

#endif