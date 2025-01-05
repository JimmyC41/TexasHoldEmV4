import { POT_UPDATE_EVENT } from "../events/gameEvents";

const potsReducer = (state = initialState, gameEvent) => {
    switch (gameEvent.type) {
        case POT_UPDATE_EVENT:
            return {
                ...state,
                updatedPots: gameEvent.payload.potUpdate
            };
        default:
            return state;
    }
}

export default potsReducer;