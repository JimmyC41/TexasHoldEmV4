import { NEXT_PLAYER_TO_ACT_EVENT } from "../grpc/gameEvents";
import { ACTION_TYPE } from "../enum";

const initialState = {
    playerToAct: 0,
    possibleActionsList: [
        {
            actionType: ACTION_TYPE.NONE,
            primaryAmount: 0,
            secondaryAmount: 0
        },
    ],
};

const playerToActReducer = (state = initialState, gameEvent) => {
    switch (gameEvent.type) {
        case NEXT_PLAYER_TO_ACT_EVENT:
            console.log('PLAYER TO ACT REDUCER receieved', gameEvent.payload);
            return {
                ...state,
                ...gameEvent.payload.playerToActInfo
            };
        default:
            return state;
    }
}

export default playerToActReducer;