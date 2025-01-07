import { NEW_STREET_EVENT } from "../grpc/GameEvents";
import { STREET } from "../enum";

const initialState = STREET.NONE

const streetReducer = (state = initialState, gameEvent) => {
    switch (gameEvent.type) {
        case NEW_STREET_EVENT:
            console.log('STREET REDUCER receieved', gameEvent.payload);
            return gameEvent.payload.newStreet;
        default:
            return state;
    }
}

export default streetReducer;