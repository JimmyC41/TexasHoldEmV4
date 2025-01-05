import { NEW_PLAYER_TO_ACT_EVENT } from "../events/gameEvents";

const playerToActReducer = (state = initialState, gameEvent) => {
    switch (gameEvent.type) {
        case NEW_PLAYER_TO_ACT_EVENT:
            return {
                ...state,
                playerToAct: gameEvent.payload.newPlayerToAct
            };
        default:
            return state;
    }
}

export default playerToActReducer;