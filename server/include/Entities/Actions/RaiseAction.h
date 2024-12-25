#ifndef RAISE_ACTION_H
#define RAISE_ACTION_H

#include "../Action.h"

class RaiseAction : public Action {
public:
    RaiseAction(string id, size_t amount) : Action(id, amount) {} 
    ActionType getActionType() const override { return ActionType::RAISE; }
};

#endif