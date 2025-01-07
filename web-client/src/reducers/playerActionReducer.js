import { NEW_PLAYER_ACTION_EVENT } from "../grpc/GameEvents";
import { ACTION_TYPE } from "../enum";

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
                ...gameEvent.payload.playerActionInfo
            };
        default:
            return state;
    }
}

export default playerActionReducer;