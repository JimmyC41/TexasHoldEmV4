import { POT_WINNER_EVENT } from "../events/gameEvents";

const initialState = [
    {
        potChips: 0,
        winner: ''
    },
];

const winnerReducer = (state = initialState, gameEvent) => {
    switch (gameEvent.type) {
        case POT_WINNER_EVENT:
            console.log('WINNER REDUCER receieved', gameEvent.payload);
            return {
                ...state,
                ...gameEvent.payload.potWinnersList
            };
        default:
            return state;
    }
}

export default winnerReducer;