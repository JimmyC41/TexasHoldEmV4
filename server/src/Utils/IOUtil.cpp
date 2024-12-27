#include "../../include/Utils/IOUtil.h"

bool IOUtil::getYesOrNo() {
    string input;

    while (true) {
        cin >> input;
        transform(input.begin(), input.end(), input.begin(), ::toupper);
        
        if (input == "Y") return true;
        else if (input == "N") return false;
        else cout << "Please enter Y or N. Try again." << endl;
    }
};

string IOUtil::getPlayerName() {
    string input;

    while (true) {
        getline(cin, input);
        if (!input.empty()) return capitaliseFirstLetter(input);
        else cout << "Name cannot be empty. Try again." << endl;
    }
}

size_t IOUtil::getPlayerChips(size_t minChips) {
    size_t chips;

    while (true) {
        cin >> chips;
        if (chips >= minChips) return chips;
        else cout << "Please enter a positive number of chips." << endl;
    }
}

pair<ActionType, size_t> IOUtil::getAction(vector<shared_ptr<PossibleAction>>& actions) {
    ActionType type = getActionType(actions);
    size_t amount = getActionAmount(actions, type);
    return {type, amount};
}

ActionType IOUtil::getActionType(vector<shared_ptr<PossibleAction>>& actions) {
    auto actionSet = getSetOfActionTypeStrings(actions);
    string action;

    while (true) {
        getline(cin, action);
        string actionLower = toLowerCase(action);
        if (actionSet.count(actionLower) != 0) return Enums::stringToActionType(actionLower);
        else cout << "Action requested is not possible. Try again." << endl;
    }
}

pair<size_t, size_t> IOUtil::getRangeOfValidAmounts(vector<shared_ptr<PossibleAction>>& actions, ActionType type) {
    for (auto& action : actions) {
        if (action->getActionType() == type) {
            return {action->getPrimaryAmount(), action->getSecondaryAmount()};
        }
    }
    return {0, 0};
}

size_t IOUtil::getActionAmount(vector<shared_ptr<PossibleAction>>& actions, ActionType type) {
    auto [primary, secondary] = getRangeOfValidAmounts(actions, type);
    if (secondary == 0) return primary;

    size_t amount;
    while (true) {
        cin >> amount;

        switch(type) {
            case ActionType::BET:
                if (amount > primary && amount < secondary) return amount;
                else cout << "Amount entered is out of bounds. Try again." << endl;
                break;
            case ActionType::RAISE:
                if (amount >= primary && amount < secondary) return amount;
                else cout << "Amount entered is out of bounds. Try again." << endl;
                break;
            default:
                return primary;
                break;
        }   
    }
}
string IOUtil::toLowerCase(const string& input) {
    string result = input;
    transform(input.begin(), input.end(), result.begin(), [](unsigned char c)
    { return ::tolower(c); });
    return result;
}

string IOUtil::capitaliseFirstLetter(const string& input) {
    if (input.empty()) return "";
    string result = input;
    result[0] = ::toupper(input[0]);
    transform(input.begin() + 1, input.end(), result.begin() +1, ::toupper);
    return result;
}

set<string> IOUtil::getSetOfActionTypeStrings(vector<shared_ptr<PossibleAction>>& actions) {
    set<string> actionSet;
    for (const auto& action : actions) {
        auto actionType = action->getActionType();
        auto actionStr = PrintUtil::actionTypeToString(actionType);
        actionSet.insert(toLowerCase(actionStr));
    }
    return actionSet;
}