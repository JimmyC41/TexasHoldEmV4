#include "../../include/gRPC/PokerServiceImpl.h"
#include "../../include/GameController.h"

#include <string>
#include <vector>
using namespace std;

PokerServiceImpl::PokerServiceImpl(GameController& ctrl) : controller(ctrl) {
    cout << "POKERSERVERIMPL CONSTRUCTED!" << endl;
}

::grpc::Status PokerServiceImpl::GameStream(::grpc::ServerContext* context, const ::GameStreamReq* request, ::grpc::ServerWriter< ::GameStreamRes>* writer) {
    return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "Method not implemented.");
}

::grpc::Status PokerServiceImpl::JoinGame(::grpc::ServerContext* context, const ::JoinGameReq* request, ::PlayerReqRes* response) {
    std::cout << "JoinGame called with player_name: " << request->player_name()
              << ", chips: " << request->chips() << std::endl;
    response->set_success(true);
    response->set_message("(Dummy) Player joined successfully!");
    return ::grpc::Status::OK;
}

::grpc::Status PokerServiceImpl::LeaveGame(::grpc::ServerContext* context, const ::LeaveGameReq* request, ::PlayerReqRes* response) {
    std::cout << "LeaveGame called!" << std::endl;
    response->set_success(true);
    response->set_message("(Dummy) Player left successfully!");
    return ::grpc::Status::OK;
}

::grpc::Status PokerServiceImpl::PlayerAction(::grpc::ServerContext* context, const ::PlayerActionReq* request, ::PlayerReqRes* response) {
    std::cout << "Player Action called!" << std::endl;
    response->set_success(true);
    response->set_message("(Dummy) Action processed succesffuly!");
    return ::grpc::Status::OK;
}

// ::grpc::Status PokerServiceImpl::JoinGame(::grpc::ServerContext* context, const ::JoinGameReq* request, ::PlayerReqRes* response) {
//     cout << "JoinGame called!" << endl;
//     string name = request->player_name();
//     uint32_t chips = request->chips();
//     vector<pair<string, uint32_t>> newPlayer = {make_pair(name, chips)};

//     bool success = controller.getPlayerManager().addNewPlayers(newPlayer);

//     if (success) {
//         response->set_success(true);
//         response->set_message("Player " + request->player_name() + " succesfully joined the game.");
//         return ::grpc::Status::OK;
//     } else {
//         response->set_success(false);
//         response->set_message("Failed to add player '" + name + "'.");
//         return ::grpc::Status(::grpc::StatusCode::INVALID_ARGUMENT, "Player Join Req Failed");
//     }
// }
