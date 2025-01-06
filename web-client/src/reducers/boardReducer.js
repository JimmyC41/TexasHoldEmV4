import { DEAL_BOARD_EVENT } from "../grpc/gameEvents";
import { SUIT, VALUE } from "../enum";

const initialState = [
    {
        suit: SUIT.NONE,
        value:VALUE.NONE
    },
];

const boardReducer = (state = initialState, gameEvent) => {
    switch (gameEvent.type) {
        case DEAL_BOARD_EVENT:
            console.log('BOARD REDUCER receieved',  gameEvent.payload)
            return {
                ...state,
                ...gameEvent.payload.communityCardsList
            };
        default:
            return state;
    }
}

export default boardReducer;