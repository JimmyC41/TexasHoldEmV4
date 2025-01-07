import { DEAL_BOARD_EVENT } from "../grpc/GameEvents";

const initialState = [];

const boardReducer = (state = initialState, gameEvent) => {
    switch (gameEvent.type) {
        case DEAL_BOARD_EVENT:
            console.log('BOARD REDUCER receieved',  gameEvent.payload)
            return gameEvent.payload.communityCardsList;
        default:
            return state;
    }
}

export default boardReducer;