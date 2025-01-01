#ifndef POSSIBLE_CALL_H
#define POSSIBLE_CALL_H

#include "../PossibleAction.h"

class PossibleCall : public PossibleAction {
public:
    PossibleCall(uint32_t amount) : PossibleAction(amount) {}
    ActionType getActionType() const override { return ActionType::CALL; }
    const uint32_t getSecondaryAmount() const override { return 0; }
};

#endif