import { DEAL_PLAYERS_EVENT } from "../grpc/GameEvents";
import { SUIT, VALUE } from "../enum";

const initialState = [];

const holeCardsReducer = (state = initialState, gameEvent) => {
    switch (gameEvent.type) {
        case DEAL_PLAYERS_EVENT:
            console.log('HOLE CARDS REDUCER receieved', gameEvent.payload);
            return gameEvent.payload.playerCardsList;
        default:
            return state;
    }
}

export default holeCardsReducer;