#ifndef ACTION_MANAGER_H
#define ACTION_MANAGER_H

#include "Entities/Action.h"
#include "Shared/GameData.h"
using namespace std;

class ActionManager {
private:
    GameData& gameData;

public:
    ActionManager();

    // Event: Triggered when a player is instructed to act in the Street In Progress state.
    // To GameData: Updates vector<shared_ptr<Action>> possibleActions attribute of the player to act.
    // From GameData: Fetches vector<shared_ptr<Action>> actionTimeline.
    vector<Action> getPossibleActions();

    // Event: Triggered when the GameController receives a valid client action in the Street in Progress state.
    // To GameData: Updates vector<shared_ptr<Action>> actionTimeline.
   void processPlayerAction();

   // Event: Triggered when the GameController processes the client action in the Street in Progress state.
   // From GameData: Fetches vector<shared_ptr<Action>> actionTimeline.
   // * may need to implement some sort of action state class
   bool isActionsFinished();
};

#endif