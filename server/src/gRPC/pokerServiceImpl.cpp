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

    bool success = controller.handleJoinGameRequest(name, chips);
    return sendPlayerReqRes(
        success,
        response,
        "Player join success!",
        "Player join failed."
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

    string name = request->player_name();

    bool success = controller.handleLeaveGameRequest(name);
    return sendPlayerReqRes(
        success,
        response,
        "Player removal success!",
        "Player removal failed."
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

    bool success = controller.handlePlayerActionRequest(id, type, amount);
    return sendPlayerReqRes(
        success,
        response,
        "Player action succcess!",
        "Player action failed."
    );
}

grpc::Status PokerServiceImpl::sendPlayerReqRes
(
    bool success,
    PlayerReqRes* response,
    const string& successMsg,
    const string& failMsg
)
{
    if (success)
    {
        response->set_success(true);
        response->set_message(successMsg);
        return grpc::Status::OK;
    }
    else
    {
        response->set_success(false);
        response->set_message(failMsg);
        return grpc::Status(
            grpc::StatusCode::INVALID_ARGUMENT,
            failMsg
        );
    }
}