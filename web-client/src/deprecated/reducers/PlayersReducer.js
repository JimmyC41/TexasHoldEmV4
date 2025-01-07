import { PLAYERS_UPDATE_EVENT } from "../../GameEvents";
import { SUIT, VALUE, POSITION, PLAYER_STATUS } from "../../enum";

const initialState = [];

const playersReducer = (state = initialState, gameEvent) => {

    switch(gameEvent.type) {
        case PLAYERS_UPDATE_EVENT:
            console.log('PLAYER ACTION REDUCER receieved', gameEvent.payload);
            return gameEvent.payload.newPlayersList;
        default:
            return state;
    }
};

export default playersReducer;