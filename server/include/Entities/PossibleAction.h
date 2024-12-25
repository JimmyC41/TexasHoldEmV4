#ifndef POSSIBLE_ACTION_H
#define POSSIBLE_ACTION_H

#include "../Shared/Enums.h"
#include <string>

using namespace std;
using ActionType = Enums::ActionType;

class PossibleAction {
private:
    size_t minAmount;
    size_t maxAmount;

public:
    PossibleAction(size_t min = 0, size_t max = 0) : minAmount(min), maxAmount(max) {}

    const size_t& getMinAmount() { return minAmount; }
    const size_t& getMaxAmount() { return maxAmount; }
    
    virtual ~PossibleAction() {}
    virtual ActionType getActionType() const = 0;
};

#endif