import { POT_WINNER_EVENT } from "../events/gameEvents";

const winnerReducer = (state = initialState, gameEvent) => {
    switch (gameEvent.type) {
        case SHOWDOWN_EVENT:
            return {
                ...state,
                potWinners: gameEvent.payload.potWinner
            };
        default:
            return state;
    }
}

export default winnerReducer;