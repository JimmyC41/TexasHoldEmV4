import { POT_UPDATE_EVENT } from "../grpc/gameEvents";

const initialState = [
    {
        potChips: 0,
        eligibleIdsList: []
    }
];

const potsReducer = (state = initialState, gameEvent) => {
    switch (gameEvent.type) {
        case POT_UPDATE_EVENT:
            console.log('POTS REDUCER', gameEvent.payload);
            return {
                ...state,
                ...gameEvent.payload.updatedPotsList
            };
        default:
            return state;
    }
}

export default potsReducer;