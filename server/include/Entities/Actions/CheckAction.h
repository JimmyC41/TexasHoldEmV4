#ifndef CHECK_ACTION_H
#define CHECK_ACTION_H

#include "../Action.h"

class CheckAction : public Action {
public:
    CheckAction(string id) : Action(id) {}
    
    ActionType getActionType() const override { return ActionType::CHECK; }
    
    size_t getAmount() const override { return 0; }
};

#endif