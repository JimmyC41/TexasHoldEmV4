import { NEW_STREET_EVENT } from "../events/gameEvents";

const streetReducer = (state = initialState, gameEvent) => {
    switch (gameEvent.type) {
        case NEW_STREET_EVENT:
            return {
                ...state,
                street: gameEvent.payload.newStreet
            };
        default:
            return state;
    }
}

export default streetReducer;