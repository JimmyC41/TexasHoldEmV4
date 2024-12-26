#ifndef ALL_IN_RAISE_ACTION_H
#define ALL_IN_RAISE_ACTION_H

#include "../Action.h"

class AllInRaiseAction : public Action {
public:
    AllInRaiseAction(string id, size_t amount) : Action(id, amount) {}
    ActionType getActionType() const override { return ActionType::ALL_IN_RAISE; }
};

#endif