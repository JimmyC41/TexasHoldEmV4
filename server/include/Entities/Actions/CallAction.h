#ifndef CALL_ACTION_H
#define CALL_ACTION_H

#include "../Action.h"

class CallAction : public Action {
private:
    size_t amount;
public:
    CallAction(string id, size_t amount) : Action(id), amount(amount) {}
    
    ActionType getActionType() const override { return ActionType::CALL; }

    size_t getAmount() const override { return amount; }
};

#endif