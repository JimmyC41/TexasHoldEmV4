#ifndef POSSIBLE_ALL_IN_BET_H
#define POSSIBLE_ALL_IN_BET_H

#include "../PossibleAction.h"

class PossibleAllInBet : public PossibleAction {
public:
    PossibleAllInBet(size_t amount) : PossibleAction(amount) {}
    ActionType getActionType() const override { return ActionType::ALL_IN_BET; }
    const size_t getSecondaryAmount() const override { return 0; }
};

#endif