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
    uint32_t primaryAmount;

public:
    PossibleAction(uint32_t amount = 0) : primaryAmount(amount) {}

    const uint32_t& getPrimaryAmount() const { return primaryAmount; }
    
    virtual ~PossibleAction() {}
    virtual const uint32_t getSecondaryAmount() const { return 0; }
    virtual ActionType getActionType() const = 0;
};

#endif