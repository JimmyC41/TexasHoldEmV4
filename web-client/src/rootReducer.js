import { combineReducers } from 'redux';

const initialState = {
    street: STREET.NONE,

    players: [
        {
            name: '',
            id: '',
            chips: 0,
            holeCards: [
                {
                    suit: SUIT.NONE,
                    value: VALUE.NONE
                }
            ],
            recentBets: 0,
            position: POSITION.LOBBY,
            status: PLAYER_STATUS.WAITING
        }
    ],

    communityCards: [
        {
            suit: SUIT.NONE,
            value:VALUE.NONE
        }
    ],

    playerToAct: '',

    lastAction: {
        playerId: '',
        action: {
            actionType: ACTION_TYPE.NONE,
            actionAmount: 0
        }
    },

    updatedPots: [
        {
            potChips: 0,
            eligibleIds: []
        }
    ],

    playersInHand: [],

    potWinners: [
        {
            potChips: 0,
            winner: ''
        }
    ]
}