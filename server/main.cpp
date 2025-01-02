#include <grpcpp/grpcpp.h>
#include "include/GameController.h"
#include "texas_holdem.grpc.pb.h"
#include "include/gRPC/PokerServiceImpl.h"

#include <iostream>
#include <memory>
#include <string>

void TestJoinGame(PokerServiceImpl& poker_service) {
    JoinGameReq request;
    request.set_player_name("Alice");
    request.set_chips(1000);

    PlayerReqRes response;
    grpc::ServerContext context;

    grpc::Status status = poker_service.JoinGame(&context, &request, &response);

    if (status.ok()) {
        std::cout << "JoinGame test call succeeded: " << response.message() << std::endl;
    } else {
        std::cout << "JoinGame test call failed: " << status.error_message() << std::endl;
    }
}

void TestLeaveGame(PokerServiceImpl& poker_service) {
    LeaveGameReq request;
    request.set_player_name("Alice");

    PlayerReqRes response;
    grpc::ServerContext context;

    grpc::Status status = poker_service.LeaveGame(&context, &request, &response);

    if (status.ok()) {
        std::cout << "LeaveGame test call succeeded: " << response.message() << std::endl;
    } else {
        std::cout << "LeaveGame test call failed: " << status.error_message() << std::endl;
    }
}

void TestPlayerAction(PokerServiceImpl& poker_service) {
    PlayerActionReq request;
    request.set_player_id("Alice");
    request.set_action_type(ProtoActionType::BET);
    request.set_action_amount(200);

    PlayerReqRes response;
    grpc::ServerContext context;

    grpc::Status status = poker_service.PlayerAction(&context, &request, &response);

    if (status.ok()) {
        std::cout << "PlayerAction test call succeeded: " << response.message() << std::endl;
    } else {
        std::cout << "PlayerAction test call failed: " << status.error_message() << std::endl;
    }
}

int main(int argc, char** argv) {
    GameController controller;
    PokerServiceImpl poker_service(controller);

    const string server_address("0.0.0.0:50051");
    grpc::ServerBuilder builder;
        
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&poker_service);

    unique_ptr<grpc::Server> server(builder.BuildAndStart());
    cout << "Server listening on " << server_address << endl;

    TestJoinGame(poker_service);
    TestLeaveGame(poker_service);
    TestPlayerAction(poker_service);

    server->Wait();
    return 0;
}