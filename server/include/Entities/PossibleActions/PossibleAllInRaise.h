#ifndef POSSIBLE_ALL_IN_RAISE_H
#define POSSIBLE_ALL_IN_RAISE_H

#include "../PossibleAction.h"

class PossibleAllInRaise : public PossibleAction {
public:
    PossibleAllInRaise(uint32_t amount) : PossibleAction(amount) {}
    ActionType getActionType() const override { return ActionType::ALL_IN_RAISE; }
    const uint32_t getSecondaryAmount() const override { return 0; }
};

#endif