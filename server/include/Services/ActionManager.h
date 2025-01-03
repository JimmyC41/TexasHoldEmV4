#ifndef ACTION_MANAGER_H
#define ACTION_MANAGER_H

#include "Entities/Action.h"
#include "Entities/Actions/AllInBetAction.h"
#include "Entities/Actions/AllInCallAction.h"
#include "Entities/Actions/AllInRaiseAction.h"
#include "Entities/Actions/BetAction.h"
#include "Entities/Actions/CallAction.h"
#include "Entities/Actions/CheckAction.h"
#include "Entities/Actions/FoldAction.h"
#include "Entities/Actions/PostSmallAction.h"
#include "Entities/Actions/PostBigAction.h"
#include "Entities/Actions/RaiseAction.h"
#include "Entities/Actions/NoneAction.h"

#include "Entities/PossibleAction.h"
#include "Entities/PossibleActions/PossibleAllInBet.h"
#include "Entities/PossibleActions/PossibleAllInCall.h"
#include "Entities/PossibleActions/PossibleAllInRaise.h"
#include "Entities/PossibleActions/PossibleBet.h"
#include "Entities/PossibleActions/PossibleCall.h"
#include "Entities/PossibleActions/PossibleCheck.h"
#include "Entities/PossibleActions/PossibleFold.h"
#include "Entities/PossibleActions/PossibleRaise.h"

#include "Shared/GameData.h"
#include "Utils/GameUtil.h"
#include "Utils/ActionUtil.h"

using namespace std;

// Struct to keep track of the number of action types
// in the current street
typedef struct StreetActionData {
    int numCalls = 0;
    int numChecks = 0;
    int numFolded = 0;
    int numAllInBet = 0;
    int numAllInCall = 0;
    int numSittingOut = 0;
    bool limpedPreflop = true;
} StreetActionData;

class ActionManager {
private:
    GameData& gameData;
    StreetActionData streetActionData;
    pair<int, bool> numPlayersInStreet; // Number of players at the start of a betting street

    void clearStreetActionData();
    
    void updateStreetActionData(ActionType actionType);

    // Players that have bet all-in do not count towards players that are 'sitting out;
    // UNLESS there are previous players that have already gone all in
    int findNumSittingOut();

    // Creates a NoneAction and sets the active action in Game Data to NoneAction
    void setActiveActionAsNone();

    // Queries gameData to find the number of players before beginning action in a street
    // Should only be called ONCE at the start of each street (bool tracks if it has been set this street)
    void setNumInitialPlayers();

    // Resets numPlayersInStreet for the next street
    void resetInitialPlayers();

public:
    ActionManager(GameData& gameData);

    // Event: Triggered when the GameController receives a valid client action in the Street in Progress state.
    // To GameData: 
    // Updates player attributes (current chips, player status, recent bet)
    // Appends the new action to the action timeline and sets the active action (if aggressive actions)
    void addNewAction(string idOrName, ActionType actionType, size_t amount = 0);

    // Event: Triggered when a player is instructed to act in the Street In Progress state.
    // To GameData: Updates possibleActions vector for the current player to act.
    // E.g. If last aggressive action was bet, the player can call, raise (if possible) or fold
    // If no aggressive action, then the player can check, bet or fold
    void generatePossibleActionsForCurPlayer();

   // Event: Triggered when the GameController processes the client action in the Street in Progress state.
   // To Game Data:
   // Resets player attributes (initialChips, recent bet)
   // Clears the action timeline and sets the active action to NoneAction
   // Returns True is all betting action is complete and the GameController can move to the next Street.
   // Note: initialPlayers is the initial number of players that began a betting street.
   bool isActionsFinished();
};

#endif