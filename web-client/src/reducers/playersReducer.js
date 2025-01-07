import { PLAYERS_UPDATE_EVENT } from "../grpc/GameEvents";
import { SUIT, VALUE, POSITION, PLAYER_STATUS } from "../enum";

const initialState = [
    {
        name: '',
        id: '',
        chips: 0,
        recentBets: 0,
        position: POSITION.LOBBY,
        status: PLAYER_STATUS.WAITING
    }
];

const playersReducer = (state = initialState, gameEvent) => {

    switch(gameEvent.type) {
        case PLAYERS_UPDATE_EVENT:
            console.log('PLAYER ACTION REDUCER receieved', gameEvent.payload);
            return {
                ...state,
                ...gameEvent.payload.newPlayersList
            };
        default:
            return state;
    }
};

export default playersReducer;