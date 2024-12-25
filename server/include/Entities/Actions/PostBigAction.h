#ifndef POST_BIG_ACTION_H
#define POST_BIG_ACTION_H

#include "../Action.h"

class PostBigAction : public Action {
public:
    PostBigAction(string id, size_t amount) : Action(id, amount) {}
    ActionType getActionType() const override { return ActionType::POST_BIG; }
};

#endif