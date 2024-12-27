#ifndef ENUMS_H
#define ENUMS_H

#include <unordered_map>
#include <string>

using namespace std;

namespace Enums {

enum class Suit {
    HEARTS = 0,
    DIAMONDS = 1,
    CLUBS = 2,
    SPADES = 3
};

enum class Value {
    TWO = 2,
    THREE = 3,
    FOUR = 4,
    FIVE = 5,
    SIX = 6,
    SEVEN = 7,
    EIGHT = 8,
    NINE = 9,
    TEN = 10,
    JACK = 11,
    QUEEN = 12,
    KING = 13,
    ACE = 14
};

enum class Position {
    LOBBY = 0,
    SMALL_BLIND,
    BIG_BLIND,
    UTG,
    UTG_1,
    MIDDLE,
    LOJACK,
    HIJACK,
    CUT_OFF,
    DEALER
};

enum class PlayerStatus {
    WAITING,
    IN_HAND,
    FOLDED,
    ALL_IN_BET,
    ALL_IN_CALL,
};

enum class Street {
    NONE,
    PRE_FLOP,
    FLOP,
    TURN,
    RIVER
};

enum class ActionType {
    NONE,
    POST_SMALL,
    POST_BIG,
    CHECK,
    BET,
    CALL,
    RAISE,
    FOLD,
    ALL_IN_BET,
    ALL_IN_CALL,
    ALL_IN_RAISE,
    INVALID_ACTION
};

enum HandCategory {
    NONE, // In Preflop, hand size is less than 5
    HIGH_CARD,
    ONE_PAIR,
    TWO_PAIR,
    THREE_OF_A_KIND,
    STRAIGHT,
    FLUSH,
    FULL_HOUSE,
    FOUR_OF_A_KIND,
    STRAIGHT_FLUSH,
    ROYAL_FLUSH
};

inline string actionTypeToString(ActionType& actionType) {
    switch(actionType) {
        case ActionType::NONE: return "None";
        case ActionType::POST_BIG: return "Big";
        case ActionType::POST_SMALL: return "Small";
        case ActionType::CHECK: return "Check";
        case ActionType::BET: return "Bet";
        case ActionType::CALL: return "Call";
        case ActionType::RAISE: return "Raise";
        case ActionType::FOLD: return "Fold";
        case ActionType::ALL_IN_BET: return "All In Bet";
        case ActionType::ALL_IN_CALL: return "All In Call";
        default: return "Unknown Action Type";
    }
}

inline ActionType stringToActionType(const string& actionStr) {
    static const unordered_map<string, ActionType> actionMap = {
        {"all in bet", ActionType::ALL_IN_BET},
        {"all in call", ActionType::ALL_IN_CALL},
        {"all in raise", ActionType::ALL_IN_RAISE},
        {"bet", ActionType::BET},
        {"call", ActionType::CALL},
        {"check", ActionType::CHECK},
        {"fold", ActionType::FOLD},
        {"raise", ActionType::RAISE},
    };
    auto it = actionMap.find(actionStr);
    if (it != actionMap.end()) return it->second;
    return ActionType::NONE;
}
}

#endif