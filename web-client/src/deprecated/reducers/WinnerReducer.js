import { POT_WINNER_EVENT } from "../../GameEvents";

const initialState = [];

const winnerReducer = (state = initialState, gameEvent) => {
    switch (gameEvent.type) {
        case POT_WINNER_EVENT:
            console.log('WINNER REDUCER receieved', gameEvent.payload);
            return gameEvent.payload.potWinnersList;
        default:
            return state;
    }
}

export default winnerReducer;