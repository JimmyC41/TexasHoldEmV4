#ifndef PROTO_UTIL_H
#define PROTO_UTIL_H

#include <memory>

#include "../Shared/Enums.h"
#include "../Entities/Player.h"
#include "texas_holdem.pb.h"

using ActionType = Enums::ActionType;
using Street = Enums::Street;
using ProtoStatus = ProtoPlayer_ProtoPlayerStatus;
using ProtoPosition = ProtoPlayer_ProtoPosition;
using ProtoValue = ProtoCard_ProtoValue;
using ProtoSuit = ProtoCard_ProtoSuit;

using namespace std;

class ProtoUtil {
public:
    static ProtoActionType toProtoType(const ActionType& type);
    static ProtoStatus toProtoStatus(const PlayerStatus& status);
    static ProtoPosition toProtoPosition(const Position& position);
    static ProtoStreet toProtoStreet(const Street& street);
    static ProtoValue toProtoValue(const Value& value);
    static ProtoSuit toProtoSuit(const Suit& suit);
    static ActionType toActionType(const ProtoActionType& type);
    static void displayEventDetails(const GameStreamRes& event);
};

#endif