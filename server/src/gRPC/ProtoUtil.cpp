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

ProtoStreet ProtoUtil::toProtoStreet(const Street& street) {
    return static_cast<ProtoStreet>(street);
}

ProtoValue ProtoUtil::toProtoValue(const Value& value) {
    return static_cast<ProtoValue>(value);
}

ProtoSuit ProtoUtil::toProtoSuit(const Suit& suit) {
    return static_cast<ProtoSuit>(static_cast<int>(suit) + 1);
}

void ProtoUtil::displayEventDetails(const GameStreamRes& event) {
    cout << "GameStreamRes Debug Output: " << endl;
    cout << event.DebugString() << endl;
}