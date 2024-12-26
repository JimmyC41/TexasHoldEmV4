#ifndef POSSIBLE_ACTION_H
#define POSSIBLE_ACTION_H

#include "../Shared/Enums.h"
#include <string>

using namespace std;
using ActionType = Enums::ActionType;

// Note: By default, a possible action has a 'default' amount
// All-In Bet, All-In Call, Call, Check and Fold all have a single 'default value'

// Bet and Raise actions are instantiated with an additional amount:
// The default acts as the minimum, and the second amount is the maximum

class PossibleAction {
private:
    size_t primaryAmount;

public:
    PossibleAction(size_t amount = 0) : primaryAmount(amount) {}

    const size_t& getPrimaryAmount() const { return primaryAmount; }
    
    virtual ~PossibleAction() {}
    virtual ActionType getActionType() const = 0;
    virtual const size_t getSecondaryAmount() const = 0;
};

#endif