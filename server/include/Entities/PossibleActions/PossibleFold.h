#ifndef POSSIBLE_FOLD_H
#define POSSIBLE_FOLD_H

#include "../PossibleAction.h"

class PossibleFold : public PossibleAction {
public:
    PossibleFold() : PossibleAction(0, 0) {}
    ActionType getActionType() const override { return ActionType::FOLD; }
};

#endif