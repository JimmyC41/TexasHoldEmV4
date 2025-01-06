#include "../../include/gRPC/PokerServiceImpl.h"
#include "../../include/GameController.h"
#include "../../include/gRPC/ProtoUtil.h"
#include "../../include/Shared/Enums.h"

#include <string>
#include <vector>
#include <chrono>
#include <thread>

using ActionType = Enums::ActionType;
using namespace std;

PokerServiceImpl::PokerServiceImpl(GameController& ctrl) : controller(ctrl) {}


grpc::Status PokerServiceImpl::GameStream
(
    grpc::ServerContext* context,
    const GameStreamReq* request,
    grpc::ServerWriter< ::GameStreamRes>* writer
)
{
    cout << "=== GRPC SERVER: Game Stream RPC ===" << endl;
    string playerId = request->player_id();
    bool success = controller.handleSubscribe(playerId, writer);

    if (!success)
    {
        return grpc::Status(
            grpc::StatusCode::INVALID_ARGUMENT,
            "Request to subscribe to the game failed.\n"
        );
    }
    else
    {
        cout << "Request to subscribe to the game succeeded!\n";
    }

    while (!context->IsCancelled())
    {
        std::this_thread::sleep_for(chrono::milliseconds(100));
    }


    controller.handleUnsubscribe(writer);    
    cout << "=== Game stream concluded for: " << playerId << " ===" << endl;
    return grpc::Status::OK;
}

grpc::Status PokerServiceImpl::JoinGame
(
    grpc::ServerContext* context,
    const JoinGameReq* request,
    PlayerReqRes* response
)
{
    string name = request->player_name();
    uint32_t chips = request->chips();

    auto [success, playerId] = controller.handleJoinGameRequest(name, chips);
    return sendPlayerReqRes
    (
        success,
        playerId,
        response,
        "Player request to join the game suceeded.",
        "Player request to join the game failed."
    );
}

grpc::Status PokerServiceImpl::LeaveGame
(
    grpc::ServerContext* context,
    const LeaveGameReq* request,
    PlayerReqRes* response
)
{
    cout << "=== GRPC SERVER: Leave Game RPC!  ===" << endl;

    string id = request->player_id();

    auto [success, playerId] = controller.handleLeaveGameRequest(id);
    return sendPlayerReqRes
    (
        success,
        playerId,
        response,
        "Player request to leave the game succeeded.",
        "Player request to leave the game failed."
    );
}

grpc::Status PokerServiceImpl::PlayerAction
(
    grpc::ServerContext* context,
    const PlayerActionReq* request,
    PlayerReqRes* response
)
{
    cout << "=== GRPC SERVER: Player Action RPC!  ===" << endl;

    string id = request->player_id();
    ActionType type = ProtoUtil::toActionType(request->action_type());
    uint32_t amount = request->action_amount();

    auto [success, playerId] = controller.handlePlayerActionRequest(id, type, amount);
    return sendPlayerReqRes
    (
        success,
        playerId,
        response,
        "Player request to enter a new action succeeded.",
        "Player request to enter a new action failed."
    );
}

grpc::Status PokerServiceImpl::sendPlayerReqRes
(
    bool success,
    const string& id,
    PlayerReqRes* response,
    const string& successMsg,
    const string& failMsg
)
{
    if (success)
    {
        response->set_success(true);
        response->set_player_id(id);
        response->set_server_message(successMsg);
        return grpc::Status::OK;
    }
    else
    {
        response->set_success(false);
        response->set_player_id(id);
        response->set_server_message(failMsg);
        return grpc::Status(grpc::StatusCode::INVALID_ARGUMENT, failMsg);
    }
}