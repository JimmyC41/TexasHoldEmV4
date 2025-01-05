import { NEW_PLAYER_ACTION_EVENT } from "../events/gameEvents";
import { ACTION_TYPE } from "../constants/enum";

const initialState =  {
    action: 
    {
        actionAmount: 0,
        actionType: ACTION_TYPE.NONE
    },
    playerId: ''
};

const playerActionReducer = (state = initialState, gameEvent) => {
    switch (gameEvent.type) {
        case NEW_PLAYER_ACTION_EVENT:
            console.log('PLAYER ACTION REDUCER receieved', gameEvent.payload);
            return {
                ...state,
                ...gameEvent.payload
            };
        default:
            return state;
    }
}

export default playerActionReducer;