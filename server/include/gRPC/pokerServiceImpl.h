#ifndef POKER_SERVICE_IMPL_H
#define POKER_SERVICE_IMPL_H

#include "texas_holdem.grpc.pb.h"
#include "../GameController.h"
#include <texas_holdem.pb.h>

using namespace texas_holdem;

class PokerServiceImpl final : public PokerService::CallbackService {
private:
    GameController& controller;
public:
    explicit PokerServiceImpl(GameController& ctrl);
    ::grpc::Status GameStream(::grpc::ServerContext* context, const ::GameStreamReq* request, ::grpc::ServerWriter< ::GameStreamRes>* writer);
    ::grpc::Status JoinGame(::grpc::ServerContext* context, const ::JoinGameReq* request, ::PlayerReqRes* response);
    ::grpc::Status LeaveGame(::grpc::ServerContext* context, const ::LeaveGameReq* request, ::PlayerReqRes* response);
    ::grpc::Status PlayerAction(::grpc::ServerContext* context, const ::PlayerActionReq* request, ::PlayerReqRes* response);
};

#endif