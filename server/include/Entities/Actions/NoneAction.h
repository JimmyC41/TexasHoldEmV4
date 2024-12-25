#ifndef NONE_ACTION_H
#define NONE_ACTION_H

#include "../Action.h"

class NoneAction : public Action {
public:
    NoneAction() : Action("None", 0) {}
    ActionType getActionType() const override { return ActionType::NONE; }
};

#endif