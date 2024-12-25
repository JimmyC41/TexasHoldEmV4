#ifndef POSSIBLE_CALL_H
#define POSSIBLE_CALL_H

#include "../PossibleAction.h"

class PossibleCall : public PossibleAction {
public:
    PossibleCall(size_t bet) : PossibleAction(bet, bet) {}
    ActionType getActionType() const override { return ActionType::CALL; }
};

#endif