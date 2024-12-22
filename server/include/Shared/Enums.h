#ifndef ENUMS_H
#define ENUMS_H

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
    LOBBY,
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
    POST_SMALL,
    POST_BIG,
    CHECK,
    BET,
    CALL,
    RAISE,
    FOLD,
    ALL_IN_BET,
    ALL_IN_CALL,
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

}

#endif