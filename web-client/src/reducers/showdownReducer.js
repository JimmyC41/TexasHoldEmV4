import { SHOWDOWN_EVENT } from "../grpc/GameEvents";

const initialState = [];

const showdownReducer = (state = initialState, gameEvent) => {
    switch (gameEvent.type) {
        case SHOWDOWN_EVENT:
            console.log('SHOWDOWN REDUCER receieved', gameEvent.payload);
            return gameEvent.payload.playersInHandList;
        default:
            return state;
    }
}

export default showdownReducer;