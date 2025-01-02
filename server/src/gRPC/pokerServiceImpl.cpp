#include "../../include/gRPC/PokerServiceImpl.h"
#include "../../include/GameController.h"
#include "../../include/gRPC/ProtoUtil.h"
#include "../../include/Shared/Enums.h"

#include <string>
#include <vector>

using ActionType = Enums::ActionType;
using namespace std;

PokerServiceImpl::PokerServiceImpl(GameController& ctrl) : controller(ctrl) {}

::grpc::Status PokerServiceImpl::GameStream(::grpc::ServerContext* context, const ::GameStreamReq* request, ::grpc::ServerWriter< ::GameStreamRes>* writer) {
    cout << "=== GRPC SERVER: Game Stream RPC! Steaming Now ===" << endl;
    
    controller.getEventManager().addSubscriber(writer);

    while (!context->IsCancelled()) {
        this_thread::sleep_for(chrono::milliseconds(100));
    }

    controller.getEventManager().removeSubscriber(writer);
    return ::grpc::Status::OK;
}

::grpc::Status PokerServiceImpl::PlayerAction(::grpc::ServerContext* context, const ::PlayerActionReq* request, ::PlayerReqRes* response) {
    cout << "=== GRPC SERVER: Player Action RPC!  ===" << endl;

    string id = request->player_id();
    ActionType type = ProtoUtil::toActionType(request->action_type());
    uint32_t amount = request->action_amount();

    controller.getActionManager().addNewAction(id, type, amount);
    controller.getIOManager().displayActionTimeline();

    response->set_success(true);
    response->set_message("Action request processed.");
    return ::grpc::Status::OK;
}

::grpc::Status PokerServiceImpl::JoinGame(::grpc::ServerContext* context, const ::JoinGameReq* request, ::PlayerReqRes* response) {
    cout << "=== GRPC SERVER: Join Game RPC!  ===" << endl;

    string name = request->player_name();
    uint32_t chips = request->chips();
    vector<pair<string, uint32_t>> newPlayer = {make_pair(name, chips)};

    bool success = controller.getPlayerManager().addNewPlayers(newPlayer);

    if (success) {
        response->set_success(true);
        response->set_message("Player " + name + " succesfully joined the game.");
        controller.getIOManager().displayPlayers();
        return ::grpc::Status::OK;
    } else {
        response->set_success(false);
        response->set_message("Failed to add player '" + name + "'.");
        return ::grpc::Status(::grpc::StatusCode::INVALID_ARGUMENT, "Unable to add a new player.");
    }
}

::grpc::Status PokerServiceImpl::LeaveGame(::grpc::ServerContext* context, const ::LeaveGameReq* request, ::PlayerReqRes* response) {
    cout << "=== GRPC SERVER: Leave Game RPC!  ===" << endl;

    string name = request->player_name();
    bool success = controller.getPlayerManager().removeExistingPlayers({name});

    if (success) {
        response->set_success(true);
        response->set_message("Player " + name + " removed from the game.");
        controller.getIOManager().displayPlayers();
        return ::grpc::Status::OK;
    } else {
        response->set_success(false);
        response->set_message("Failed to remove player '" + name + "'.");
        return ::grpc::Status(::grpc::StatusCode::INVALID_ARGUMENT, "Unable to remove player. Player does not exist.");
    }
}
