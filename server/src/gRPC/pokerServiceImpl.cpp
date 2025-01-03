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
    string playerId = request->player_id();
    cout << "=== GRPC SERVER: Game Stream RPC receieved for id:  " << playerId << " ===" << endl;

    bool success = controller.handleSubscribe(playerId, writer);

    if (!success) {
        return ::grpc::Status(::grpc::StatusCode::INVALID_ARGUMENT, "Cannot subscribe a player that does not exist.");
    }

    while (!context->IsCancelled()) {
        this_thread::sleep_for(chrono::milliseconds(100));
    }

    controller.handleUnsubscribe(writer);
    
    cout << "=== GRPC SERVER: Game Stream RPC ended for id:  " << playerId << " ===" << endl;
    return ::grpc::Status::OK;
}

::grpc::Status PokerServiceImpl::JoinGame(::grpc::ServerContext* context, const ::JoinGameReq* request, ::PlayerReqRes* response) {
    cout << "=== GRPC SERVER: Join Game RPC!  ===" << endl;

    string name = request->player_name();
    uint32_t chips = request->chips();

    bool success = controller.handleJoinGameRequest(name, chips);

    if (success) {
        response->set_success(true);
        response->set_message("Player " + name + " was added to the queue to join the game!");
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

    bool success = controller.handleLeaveGameRequest(name);

    if (success) {
        response->set_success(true);
        response->set_message("Player " + name + " was added to the queue to leave the game.");
        return ::grpc::Status::OK;
    } else {
        response->set_success(false);
        response->set_message("Failed to remove player '" + name + "'.");
        return ::grpc::Status(::grpc::StatusCode::INVALID_ARGUMENT, "Unable to remove player. Player does not exist.");
    }
}

::grpc::Status PokerServiceImpl::PlayerAction(::grpc::ServerContext* context, const ::PlayerActionReq* request, ::PlayerReqRes* response) {
    cout << "=== GRPC SERVER: Player Action RPC!  ===" << endl;

    string id = request->player_id();
    ActionType type = ProtoUtil::toActionType(request->action_type());
    uint32_t amount = request->action_amount();

    bool success = controller.handlePlayerActionRequest(id, type, amount);

    if (success) {
        response->set_success(true);
        response->set_message("Valid action received for " + id + ".");
        return ::grpc::Status::OK;
    } else {
        response->set_success(false);
        response->set_message("Invalid action receieved for '" + id + "'.");
        return ::grpc::Status(::grpc::StatusCode::INVALID_ARGUMENT, "Action receieved does not match valid possible actions.");
    }
}