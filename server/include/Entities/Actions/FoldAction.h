#ifndef FOLD_ACTION_H
#define FOLD_ACTION_H

#include "../Action.h"

class FoldAction : public Action {
public:
    FoldAction(string id) : Action(id) {}
    ActionType getActionType() const override { return ActionType::FOLD; }
};

#endif