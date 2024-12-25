#ifndef POST_SMALL_ACTION_H
#define POST_SMALL_ACTION_H

#include "../Action.h"

class PostSmallAction : public Action {
public:
    PostSmallAction(string id, size_t amount) : Action(id, amount) {}
    ActionType getActionType() const override { return ActionType::POST_SMALL; }
};

#endif