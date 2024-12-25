#ifndef POSSIBLE_CHECK_H
#define POSSIBLE_CHECK_H

#include "../PossibleAction.h"

class PossibleCheck : public PossibleAction {
public:
    PossibleCheck() : PossibleAction(0, 0) {}
    ActionType getActionType() const override { return ActionType::CHECK; }
};

#endif