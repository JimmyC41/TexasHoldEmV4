import { DEAL_PLAYERS_EVENT } from "../events/gameEvents";
import { SUIT, VALUE } from "../constants/enum";

const initialState = [
    {
        playerId: 0,
        holeCards: [
            {
                suit: SUIT.NONE,
                value: VALUE.NONE
            }
        ],
    },
];

const holeCardsReducer = (state = initialState, gameEvent) => {
    switch (gameEvent.type) {
        case DEAL_PLAYERS_EVENT:
            console.log('HOLE CARDS REDUCER receieved', gameEvent.payload);
            return {
                ...state,
                ...gameEvent.payload
            };
        default:
            return state;
    }
}

export default holeCardsReducer;