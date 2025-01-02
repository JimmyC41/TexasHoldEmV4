#include "../../include/Services/EventManager.h"
#include "../../include/Entities/Player.h"
#include "../../include/gRPC/ProtoUtil.h"

EventManager::EventManager(GameData& gameData) : gameData(gameData) {}

void EventManager::addSubscriber(grpc::ServerWriter<GameStreamRes>* writer) {
    lock_guard<mutex> lock(subscriberMutex);

    cout << "(+) Event Manager: Adding a new subscriber!\n" << endl;
    subscribers.insert(writer);
}

void EventManager::removeSubscriber(grpc::ServerWriter<GameStreamRes>* writer) {
    lock_guard<mutex> lock(subscriberMutex);

    cout << "(+) Event Manager: Removing an existing subscriber!\n" << endl;
    subscribers.erase(writer);
}

void EventManager::publishEvent(const GameStreamRes& event) {
    lock_guard<mutex> lock(subscriberMutex);

    cout << "(+) Event Manager: Publishing an event to " << subscribers.size() << "subscribers.\n" << endl;
    for (auto it = subscribers.begin(); it != subscribers.end(); ) {
        if (!(*it)->Write(event)) it = subscribers.erase(it);
        else ++it;
    }
}

void EventManager::publishPlayersUpdateEvent() {
    cout << "(+) Event Manager: Players updated!" << endl;
    GameStreamRes event;
    PlayersUpdateEvent* playersUpdate = event.mutable_players_update();

    vector<shared_ptr<Player>> players = gameData.getPlayers();
    for (const auto& player : players) {
        ProtoPlayer* cur = playersUpdate->add_new_players();
        cur->set_name(player->getName());
        cur->set_chips(player->getCurChips());
        cur->set_recent_bets(player->getRecentBet());
        cur->set_status(ProtoUtil::toProtoStatus(player->getPlayerStatus()));
        cur->set_position(ProtoUtil::toProtoPosition(player->getPosition()));
    }
    publishEvent(event);
}

void EventManager::publishNewStreetEvent() {

}

void EventManager::publishDealPlayersEvent() {

}


void EventManager::publishDealBoardEvent() {

}

void EventManager::publishNewPlayerToActEvent() {

}
void EventManager::publishNewPlayerActionEvent() {

}
void EventManager::publishPotUpdateEvent() {

}
void EventManager::publishShowdownEvent() {

}
void EventManager::publishPotWinnerEvent() {

}