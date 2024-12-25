#ifndef ALL_IN_BET_ACTION_H
#define ALL_IN_BET_ACTION_H

#include "../Action.h"

class AllInBetAction : public Action {
public:
    AllInBetAction(string id, size_t amount) : Action(id, amount) {}
    ActionType getActionType() const override { return ActionType::ALL_IN_BET; }
};

#endif