#ifndef ALL_IN_BET_ACTION_H
#define ALL_IN_BET_ACTION_H

#include "../Action.h"

class AllInBetAction : public Action {
private:
    size_t amount;
public:
    AllInBetAction(string id, size_t amount) : Action(id), amount(amount) {}
    
    ActionType getActionType() const override { return ActionType::ALL_IN_BET; }

    size_t getAmount() const override { return amount; }
};

#endif