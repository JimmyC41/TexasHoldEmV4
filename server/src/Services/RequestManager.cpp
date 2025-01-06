#include "../../include/Services/RequestManager.h"
#include "../../include/Utils/PlayerUtil.h"

RequestManager::RequestManager() :
    playerJoinQueue(),
    playerLeaveQueue(),
    actionQueue(),
    joinMtx(),
    leaveMtx(),
    actionMtx(),
    joinCV(),
    leaveCV(),
    actionCV()
    {}

// PLAYER JOIN METHODS

string RequestManager::addToPlayerJoinQueue(const string& name, const uint32_t& chips) {
    lock_guard<mutex> lock(joinMtx);

    string playerId = PlayerUtil::generateUUID();
    playerJoinQueue.emplace(name, chips, playerId);
    joinCV.notify_one(); // Notify waiting thread

    return playerId; // Return to playerId (used as a session token)
}

tuple<string, uint32_t, string> RequestManager::getJoinRequest() {
    unique_lock<mutex> lock(joinMtx);

    // Wait until we are notified of a new join request
    // and the player join queue is not empty
    joinCV.wait(lock, [this] { return !playerJoinQueue.empty(); });

    auto joinRequest = playerJoinQueue.front();
    playerJoinQueue.pop();
    return joinRequest;
}

bool RequestManager::isJoinQueueEmpty() {
    lock_guard<mutex> lock(joinMtx);
    return playerJoinQueue.empty();
}

int RequestManager::getNumInPlayerJoinQueue() {
    lock_guard<mutex> lock(joinMtx);
    return playerJoinQueue.size();
}

// PLAYER LEAVE METHODS

void RequestManager::addToPlayerLeaveQueue(const string& name) {
    lock_guard<mutex> lock(leaveMtx);
    playerLeaveQueue.emplace(name);
    leaveCV.notify_one(); // Notify waiting thread
}

string RequestManager::getLeaveRequest() {
    unique_lock<mutex> lock(leaveMtx);

    // Wait until we are notified of a new leave request
    // and the player join queue is not empty
    leaveCV.wait(lock, [this] { return !playerLeaveQueue.empty(); });

    auto leaveRequest = playerLeaveQueue.front();
    playerLeaveQueue.pop();
    return leaveRequest;
}

bool RequestManager::isLeaveQueueEmpty() {
    lock_guard<mutex> lock(leaveMtx);
    return playerLeaveQueue.empty();
}

// PLAYER ACTION METHODS

void RequestManager::addToActionQueue(const ActionType& type, const uint32_t& amount) {
    lock_guard<mutex> lock(actionMtx);
    actionQueue.emplace(type, amount);
    actionCV.notify_one();
}

pair<ActionType, uint32_t> RequestManager::getActionRequest() {
    unique_lock<mutex> lock(actionMtx);

    // Wait until we are notified of a new action request
    // and the action queue is not empty
    actionCV.wait(lock, [this] { return !actionQueue.empty(); });

    auto actionRequest = actionQueue.front();
    actionQueue.pop();
    return actionRequest;
}