#ifndef BET_ACTION_H
#define BET_ACTION_H

#include "../Action.h"

class BetAction : public Action {
private:
    size_t amount;
public:
    BetAction(string id, size_t amount) : Action(id), amount(amount) {}
    
    ActionType getActionType() const override { return ActionType::BET; }

    size_t getAmount() const override { return amount; }
};

#endif