#include "../../include/Services/RequestManager.h"

RequestManager::RequestManager() :
    playerJoinQueue(),
    playerLeaveQueue(),
    joinMtx(),
    leaveMtx(),
    joinCV(),
    leaveCV()
    {}

// PLAYER JOIN METHODS

void RequestManager::addToPlayerJoinQueue(const string& name, const uint32_t& chips) {
    lock_guard<mutex> lock(joinMtx);
    playerJoinQueue.emplace(name, chips);
    joinCV.notify_one(); // Notify waiting thread
}

pair<string, int32_t> RequestManager::getJoinRequest() {
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