import { PLAYERS_UPDATE_EVENT } from "../events/gameEvents";
import { SUIT, VALUE, POSITION, PLAYERSTATUS } from "../constants/enum"

const playersReducer = (state = initialState, gameEvent) => {
    switch(gameEvent.type) {
        case PLAYERS_UPDATE_EVENT:
            return {
                ...state,
                players: gameEvent.payload.playersUpdate
            };
        default:
            return state;
    }
};

export default playersReducer;