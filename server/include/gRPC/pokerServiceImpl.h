#ifndef POKER_SERVICE_IMPL_H
#define POKER_SERVICE_IMPL_H

#include "texas_holdem.grpc.pb.h"
#include "texas_holdem.pb.h"

class GameController;

using namespace std;

/**
 * Services provided by the gRPC server.
 */
class PokerServiceImpl final : public PokerService::Service {
private:
    GameController& controller;

    /* Response sent to gRPC client for unary call requests. */
    grpc::Status sendPlayerReqRes
    (
        bool success,
        const string& id,
        PlayerReqRes* response,
        const string& succcessMsg,
        const string& failMsg
    );

public:
    explicit PokerServiceImpl(GameController& ctrl);

    /* gRPC service to subscribe clients to game events. */
    grpc::Status GameStream
    (
        grpc::ServerContext* context,
        const GameStreamReq* request,
        grpc::ServerWriter< ::GameStreamRes>* writer
    );

    /* gRPC service to add players to the game. */
    grpc::Status JoinGame
    (
        grpc::ServerContext* context,
        const JoinGameReq* request,
        PlayerReqRes* response
    );

    /* gRPC service to leave the game. */
    grpc::Status LeaveGame
    (
        grpc::ServerContext* context,
        const LeaveGameReq* request,
        PlayerReqRes* response
    );

    /* gRPC service to process a player action.*/
    grpc::Status PlayerAction
    (
        grpc::ServerContext* context,
        const PlayerActionReq* request,
        PlayerReqRes* response
    );
};

#endif