#ifndef POSSIBLE_RAISE_H
#define POSSIBLE_RAISE_H

#include "../PossibleAction.h"

class PossibleRaise : public PossibleAction {
private:
uint32_t secondaryAmount;
public:
    PossibleRaise(uint32_t min, uint32_t max) : PossibleAction(min), secondaryAmount(max) {}
    ActionType getActionType() const override {return ActionType::RAISE; }
    const uint32_t getSecondaryAmount() const override { return secondaryAmount; }
};

#endif