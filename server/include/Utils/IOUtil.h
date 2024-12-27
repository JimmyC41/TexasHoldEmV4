#ifndef IO_UTIL_H
#define IO_UTIL_H

#include "../Entities/PossibleAction.h"
#include "../Shared/Enums.h"
#include "../Shared/GameData.h"
#include "../Utils/PrintUtil.h"

#include <vector>
#include <iostream>
#include <sstream>
#include <set>
#include <unordered_map>


using ActionType = Enums::ActionType;

class IOUtil {
public:
    static bool getYesOrNo();
    static string getPlayerName();
    static size_t getPlayerChips(size_t minChips);
    static pair<ActionType, size_t> getAction(vector<shared_ptr<PossibleAction>>& actions);
    static ActionType getActionType(vector<shared_ptr<PossibleAction>>& actions);
    static pair<size_t, size_t> getRangeOfValidAmounts(vector<shared_ptr<PossibleAction>>& actions, ActionType type);
    static size_t getActionAmount(vector<shared_ptr<PossibleAction>>& actions, ActionType type);

    // String Helper Methods
    static string toLowerCase(const string& input);
    static string capitaliseFirstLetter(const string& input);
    static set<string> getSetOfActionTypeStrings(vector<shared_ptr<PossibleAction>>& actions);
};

#endif