#include "include/GameController.h"

int main() {
    GameController controller;
    controller.startGame();
    return 0;

//     #include <grpcpp/grpcpp.h>
// #include "PokerServiceImpl.h"

// int main() {
//     GameController controller;  // Your game controller instance
//     PokerServiceImpl service(controller);

//     std::string server_address("0.0.0.0:50051");
//     ::grpc::ServerBuilder builder;
//     builder.AddListeningPort(server_address, ::grpc::InsecureServerCredentials());
//     builder.RegisterService(&service);

//     std::unique_ptr<::grpc::Server> server(builder.BuildAndStart());
//     std::cout << "Server listening on " << server_address << std::endl;

//     server->Wait();
//     return 0;
// }
}