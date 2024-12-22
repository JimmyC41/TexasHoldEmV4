#ifndef RAISE_ACTION_H
#define RAISE_ACTION_H

#include "../Action.h"

class RaiseAction : public Action {
private:
    size_t amount;
public:
    RaiseAction(string id, size_t amount) : Action(id), amount(amount) {}
    
    ActionType getActionType() const override { return ActionType::RAISE; }

    size_t getAmount() const override { return amount; }
};

#endif