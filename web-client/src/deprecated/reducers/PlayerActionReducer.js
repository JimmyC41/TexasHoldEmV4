import { NEW_PLAYER_ACTION_EVENT } from "../../GameEvents";
import { ACTION_TYPE } from "../../enum";

const initialState =  {};

const playerActionReducer = (state = initialState, gameEvent) => {
    switch (gameEvent.type) {
        case NEW_PLAYER_ACTION_EVENT:
            console.log('PLAYER ACTION REDUCER receieved', gameEvent.payload);
            return gameEvent.payload.playerActionInfo;
        default:
            return state;
    }
}

export default playerActionReducer;