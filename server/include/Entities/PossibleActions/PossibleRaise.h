#ifndef POSSIBLE_RAISE_H
#define POSSIBLE_RAISE_H

#include "../PossibleAction.h"

class PossibleRaise : public PossibleAction {
public:
    PossibleRaise(size_t min, size_t max) : PossibleAction(min, max) {}
    ActionType getActionType() const override {return ActionType::RAISE; }
};

#endif