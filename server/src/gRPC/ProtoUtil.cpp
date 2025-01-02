#include "../../include/gRPC/ProtoUtil.h"

ProtoActionType ProtoUtil::toProtoType(const ActionType& type) {
    return static_cast<ProtoActionType>(type);
}

ActionType ProtoUtil::toActionType(const ProtoActionType& type) {
    return static_cast<ActionType>(type);
}

ProtoStatus ProtoUtil::toProtoStatus(const PlayerStatus& status) {
    return static_cast<ProtoStatus>(status);
}

ProtoPosition ProtoUtil::toProtoPosition(const Position& position) {
    return static_cast<ProtoPosition>(position);
}

void ProtoUtil::displayEventDetails(const GameStreamRes& event) {
    cout << "GameStreamRes Debug Output: " << endl;
    cout << event.DebugString() << endl;
}