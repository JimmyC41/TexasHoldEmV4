#ifndef GAME_QUEUE_MANGER
#define GAME_QUEUE_MANAGER

#include <mutex>
#include <queue>
#include <string>
#include <utility>
#include <condition_variable>

using namespace std;

class RequestManager {
private:
    queue<pair<string, uint32_t>> playerJoinQueue;
    queue<string> playerLeaveQueue;
    mutex joinMtx, leaveMtx;
    condition_variable joinCV, leaveCV;

public:
    RequestManager();

    // Adds a new join request 
    void addToPlayerJoinQueue(const string& name, const uint32_t& chips);

    // Adds a leave request
    void addToPlayerLeaveQueue(const string& name);

    // Gets the next join request from queue (blocks if empty)
    pair<string, int32_t> getJoinRequest();

    // Gets the next leave request from queue (blocks if empty)
    string getLeaveRequest();

    // Check if the join queue is empty
    bool isJoinQueueEmpty();

    // Check if the leave queue is empty
    bool isLeaveQueueEmpty();
};


#endif