#ifndef POSSIBLE_RAISE_H
#define POSSIBLE_RAISE_H

#include "../PossibleAction.h"

class PossibleRaise : public PossibleAction {
private:
size_t secondaryAmount;
public:
    PossibleRaise(size_t min, size_t max) : PossibleAction(min), secondaryAmount(max) {}
    ActionType getActionType() const override {return ActionType::RAISE; }
    const size_t getSecondaryAmount() const override { return secondaryAmount; }
};

#endif