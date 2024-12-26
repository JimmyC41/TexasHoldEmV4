#ifndef POSSIBLE_CHECK_H
#define POSSIBLE_CHECK_H

#include "../PossibleAction.h"

class PossibleCheck : public PossibleAction {
public:
    PossibleCheck() : PossibleAction(0) {}
    ActionType getActionType() const override { return ActionType::CHECK; }
    const size_t getSecondaryAmount() const override { return 0; }
};

#endif