#ifndef BET_ACTION_H
#define BET_ACTION_H

#include "../Action.h"

class BetAction : public Action {
public:
    BetAction(string id, size_t amount) : Action(id, amount) {}
    ActionType getActionType() const override { return ActionType::BET; }
};

#endif