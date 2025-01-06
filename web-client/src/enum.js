export const STREET = {
    NONE: 0,
    PRE_FLOP: 1,
    FLOP: 2,
    TURN: 3,
    RIVER: 4
}

export const SUIT = {
    NONE: 0,
    HEARTS: 1,
    DIAMONDS: 2,
    CLUBS: 3,
    SPADES: 4
};

export const VALUE = {
    NONE: 0,
    TWO: 2,
    THREE: 3,
    FOUR: 4,
    FIVE: 5,
    SIX: 6,
    SEVEN: 7,
    EIGHT: 8,
    NINE: 9,
    TEN: 10,
    JACK: 11,
    QUEEN: 12,
    KING: 13,
    ACE: 14
}

export const POSITION = {
    LOBBY: 0,
    SMALL_BLIND: 1,
    BIG_BLIND: 2,
    UTG: 3,
    UTG_1: 4,
    MIDDLE: 5,
    LOJACK: 6,
    HIJACK: 7,
    CUT_OFF: 8,
    DEALER: 9
}

export const PLAYER_STATUS = {
    WAITING: 0,
    IN_HAND: 1,
    FOLDED: 2,
    ALL_IN_BET: 3,
    ALL_IN_CALL: 4
}

export const ACTION_TYPE = {
    NONE: 0,
    POST_SMALL: 1,
    POST_BIG: 2,
    CHECK: 3,
    BET: 4,
    CALL: 5,
    RAISE: 6,
    FOLD: 7,
    ALL_IN_BET: 8,
    ALL_IN_CALL: 9,
    ALL_IN_RAISE: 10
}