import { DEAL_BOARD_EVENT } from "../events/gameEvents";
import { SUIT, VALUE } from "../constants/enum";

const boardReducer = (state = initialState, gameEvent) => {
    switch (gameEvent.type) {
        case DEAL_BOARD_EVENT:
            return {
                ...state,
                communityCards: gameEvent.payload.dealBoard
            };
        default:
            return state;
    }
}

export default boardReducer;