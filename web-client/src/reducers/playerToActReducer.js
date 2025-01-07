import { NEXT_PLAYER_TO_ACT_EVENT } from "../grpc/GameEvents";
import { ACTION_TYPE } from "../enum";

const initialState = {};

const playerToActReducer = (state = initialState, gameEvent) => {
    switch (gameEvent.type) {
        case NEXT_PLAYER_TO_ACT_EVENT:
            console.log('PLAYER TO ACT REDUCER receieved', gameEvent.payload);
            return gameEvent.payload.playerToActInfo;
        default:
            return state;
    }
}

export default playerToActReducer;