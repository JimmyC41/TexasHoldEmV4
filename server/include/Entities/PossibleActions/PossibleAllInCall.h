#ifndef POSSIBLE_ALL_IN_CALL_H
#define POSSIBLE_ALL_IN_CALL_H

#include "../PossibleAction.h"

class PossibleAllInCall : public PossibleAction {
public:
    PossibleAllInCall(uint32_t amount) : PossibleAction(amount) {}
    ActionType getActionType() const override { return ActionType::ALL_IN_CALL; }
    const uint32_t getSecondaryAmount() const override { return 0; }
};

#endif