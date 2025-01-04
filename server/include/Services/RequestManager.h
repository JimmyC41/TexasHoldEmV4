#ifndef REQUEST_MANAGER
#define REQUEST_MANAGER

#include "../Shared/Enums.h"
#include <mutex>
#include <queue>
#include <string>
#include <utility>
#include <condition_variable>

using ActionType = Enums::ActionType;
using namespace std;

class RequestManager {
private:
    queue<pair<string, uint32_t>> playerJoinQueue;
    queue<string> playerLeaveQueue;
    queue<pair<ActionType, uint32_t>> actionQueue;
    mutex joinMtx, leaveMtx, actionMtx;
    condition_variable joinCV, leaveCV, actionCV;

public:
    RequestManager();

    // Adds a new join request 
    void addToPlayerJoinQueue(const string& name, const uint32_t& chips);

    // Adds a leave request
    void addToPlayerLeaveQueue(const string& name);

    // Adds a new action request
    void addToActionQueue(const ActionType& type, const uint32_t& amount = 0);

    // Gets the next join request from queue (blocks if empty)
    pair<string, uint32_t> getJoinRequest();

    // Gets the next leave request from queue (blocks if empty)
    string getLeaveRequest();

    // Gets the next action request from queue (blocks if empty)
    pair<ActionType, uint32_t> getActionRequest();

    // Check if the join queue is empty
    bool isJoinQueueEmpty();

    // Check if the leave queue is empty
    bool isLeaveQueueEmpty();

    // Returns the number of players waiting in the queue
    int getNumInPlayerJoinQueue();
};


#endif