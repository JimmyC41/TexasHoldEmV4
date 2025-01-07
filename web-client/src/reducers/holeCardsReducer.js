import { DEAL_PLAYERS_EVENT } from "../grpc/GameEvents";
import { SUIT, VALUE } from "../enum";

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
                ...gameEvent.payload.playerCardsList
            };
        default:
            return state;
    }
}

export default holeCardsReducer;