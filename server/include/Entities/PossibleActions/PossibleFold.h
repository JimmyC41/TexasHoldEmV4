#ifndef POSSIBLE_FOLD_H
#define POSSIBLE_FOLD_H

#include "../PossibleAction.h"

class PossibleFold : public PossibleAction {
public:
    PossibleFold() : PossibleAction(0) {}
    ActionType getActionType() const override { return ActionType::FOLD; }
    const size_t getSecondaryAmount() const override { return 0; }
};

#endif