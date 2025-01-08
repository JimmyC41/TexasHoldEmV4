#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H

#include <grpcpp/grpcpp.h>
#include <mutex>
#include <unordered_set>
#include <memory>

#include "texas_holdem.pb.h"
#include "texas_holdem.grpc.pb.h"
#include "../Shared/GameData.h"

using namespace std;

class EventManager {
private:
    GameData& gameData;
    unordered_set<grpc::ServerWriter<GameStreamRes>*> subscribers;
    mutex subscriberMutex;

    void publishEvent(const GameStreamRes& event);
    void logJsonOutput(const GameStreamRes& event);
public:
    EventManager(GameData& gameData);
    void addSubscriber(grpc::ServerWriter<GameStreamRes>* subscriber);
    void removeSubscriber(grpc::ServerWriter<GameStreamRes>* subscriber);
    bool allPlayersSubscribed();

    void publishPlayersUpdateEvent();
    void publishNewStreetEvent();
    void publishDealPlayersEvent();
    void publishDealBoardEvent();
    void publishNewPlayerToActEvent();
    void publishNewPlayerActionEvent();
    void publishPotUpdateEvent();
    void publishShowdownEvent();
    void publishPotWinnerEvent();
};


#endif