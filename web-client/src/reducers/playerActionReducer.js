import { NEW_PLAYER_ACTION_EVENT } from "../events/gameEvents";
import { ACTION_TYPE } from "../constants/enum";

const playerActionReducer = (state = initialState, gameEvent) => {
    switch (gameEvent.type) {
        case NEW_PLAYER_ACTION_EVENT:
            return {
                ...state,
                lastAction: gameEvent.payload.newPlayerAction
            };
        default:
            return state;
    }
}

export default playerActionReducer;