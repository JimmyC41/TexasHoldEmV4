#ifndef ALL_IN_CALL_H
#define ALL_IN_CALL_H

#include "../Action.h"

class AllInCallAction : public Action {
private:
    size_t amount;
public:
    AllInCallAction(string id, size_t amount) : Action(id), amount(amount) {}
    
    ActionType getActionType() const override { return ActionType::ALL_IN_CALL; }

    size_t getAmount() const override { return amount; }
};

#endif