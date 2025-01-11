#ifndef POSSIBLE_BET_H
#define POSSIBLE_BET_H

#include "../PossibleAction.h"

class PossibleBet : public PossibleAction {
private:
    uint32_t secondaryAmount;
public:
    PossibleBet(uint32_t max) : PossibleAction(0), secondaryAmount(max) {}

    ActionType getActionType() const override { return ActionType::BET; }
    const uint32_t getSecondaryAmount() const override { return secondaryAmount; }
};

#endif