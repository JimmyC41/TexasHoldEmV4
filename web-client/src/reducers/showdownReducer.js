import { SHOWDOWN_EVENT } from "../events/gameEvents";

const showdownReducer = (state = initialState, gameEvent) => {
    switch (gameEvent.type) {
        case SHOWDOWN_EVENT:
            return {
                ...state,
                playersInHand: gameEvent.payload.showdown
            };
        default:
            return state;
    }
}

export default showdownReducer;