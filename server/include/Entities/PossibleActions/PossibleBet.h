#ifndef POSSIBLE_BET_H
#define POSSIBLE_BET_H

#include "../PossibleAction.h"

class PossibleBet : public PossibleAction {
private:
    size_t secondaryAmount;
public:
    PossibleBet(size_t max) : PossibleAction(0), secondaryAmount(max) {}

    ActionType getActionType() const override { return ActionType::BET; }
    const size_t getSecondaryAmount() const override { return secondaryAmount; }
};

#endif