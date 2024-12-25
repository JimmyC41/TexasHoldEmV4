#ifndef CALL_ACTION_H
#define CALL_ACTION_H

#include "../Action.h"

class CallAction : public Action {
public:
    CallAction(string id, size_t amount) : Action(id, amount) {}
    ActionType getActionType() const override { return ActionType::CALL; }
};

#endif