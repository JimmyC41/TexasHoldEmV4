#ifndef POSSIBLE_ACTION_H
#define POSSIBLE_ACTION_H

#include "../Shared/Enums.h"
#include <string>

using namespace std;
using ActionType = Enums::ActionType;


/**
 * By default, a possible action has a primary amount.
 * All-In Bet, All-In Call, Call, Check and Fold all have a 'default' primary amount.
 * That is, such actions can only take on one possile values.
 * Bet and Raise actions are instantiated with an secondary amount because they can take on a range of values.
 * In this case, the primaryAmount acts as the minimum, and the secondaryAmount acts as the maximum.
 */

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