import { POT_UPDATE_EVENT } from "../../GameEvents";

const initialState = [];

const potsReducer = (state = initialState, gameEvent) => {
    switch (gameEvent.type) {
        case POT_UPDATE_EVENT:
            console.log('POTS REDUCER', gameEvent.payload);
            return gameEvent.payload.updatedPotsList;
        default:
            return state;
    }
}

export default potsReducer;