#ifndef ALL_IN_CALL_H
#define ALL_IN_CALL_H

#include "../Action.h"

class AllInCallAction : public Action {
public:
    AllInCallAction(string id, uint32_t amount) : Action(id, amount) {}
    ActionType getActionType() const override { return ActionType::ALL_IN_CALL; }
};

#endif