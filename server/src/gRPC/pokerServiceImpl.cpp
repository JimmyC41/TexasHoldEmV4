#include "../../include/gRPC/pokerServiceImpl.h"

#include <string>
#include <vector>
using namespace std;

PokerServiceImpl::PokerServiceImpl(GameController& ctrl) : controller(ctrl) {}

::grpc::Status PokerServiceImpl::GameStream(::grpc::ServerContext* context, const ::GameStreamReq* request, ::grpc::ServerWriter< ::GameStreamRes>* writer) {
    return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "Method not implemented.");
}

::grpc::Status PokerServiceImpl::JoinGame(::grpc::ServerContext* context, const ::JoinGameReq* request, ::PlayerReqRes* response) {
    string name = request->player_name();
    uint32_t chips = request->chips();
    vector<pair<string, uint32_t>> newPlayer = {make_pair(name, chips)};

    bool success = controller.getPlayerManager().addNewPlayers(newPlayer);

    if (success) {
        response->set_success(true);
        response->set_message("Player " + request->player_name() + " succesfully joined the game.");
        return ::grpc::Status::OK;
    } else {
        response->set_success(false);
        response->set_message("Failed to add player '" + name + "'.");
        return ::grpc::Status(::grpc::StatusCode::INVALID_ARGUMENT, "Player Join Req Failed");
    }
}

::grpc::Status PokerServiceImpl::LeaveGame(::grpc::ServerContext* context, const ::LeaveGameReq* request, ::PlayerReqRes* response) {
    return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "Method not implemented.");
}

::grpc::Status PokerServiceImpl::PlayerAction(::grpc::ServerContext* context, const ::PlayerActionReq* request, ::PlayerReqRes* response) {
    return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "Method not implemented.");
}

