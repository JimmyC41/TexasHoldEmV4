#ifndef POSSIBLE_BET_H
#define POSSIBLE_BET_H

#include "../PossibleAction.h"

class PossibleBet : public PossibleAction {
public:
    PossibleBet(size_t bet) : PossibleAction(0, bet) {}
    ActionType getActionType() const override {return ActionType::BET; }
};

#endif