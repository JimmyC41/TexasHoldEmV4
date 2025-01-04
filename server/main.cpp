#include <grpcpp/grpcpp.h>
#include "include/GameController.h"
#include "texas_holdem.grpc.pb.h"
#include "include/gRPC/PokerServiceImpl.h"

#include <iostream>
#include <memory>
#include <string>
#include <chrono>
#include <thread>

int main(int argc, char** argv) {
    GameController controller;
    PokerServiceImpl poker_service(controller);

    const string server_address("localhost:9090");    
    grpc::ServerBuilder builder;
        
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&poker_service);

    unique_ptr<grpc::Server> server(builder.BuildAndStart());
    cout << "Server listening on " << server_address << endl;

    thread game_thread([&controller]() { controller.startGame(); });

    server->Wait();

    if (game_thread.joinable()) {
        game_thread.join();
    }
    return 0;
}