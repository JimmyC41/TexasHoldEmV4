import {
    NEW_STREET_EVENT,
    PLAYERS_UPDATE_EVENT,
    DEAL_PLAYERS_EVENT,
    DEAL_BOARD_EVENT,
    NEXT_PLAYER_TO_ACT_EVENT,
    NEW_PLAYER_ACTION_EVENT,
    POT_UPDATE_EVENT,
    SHOWDOWN_EVENT,
    POT_WINNER_EVENT
} from './GameEvents';

export const initialState = {
    street: {},
    players: [],
    holeCards: [],
    board: [],
    nextPlayerToAct: {},
    newPlayerAction: {},
    pots: [],
    showdownPlayers: [],
    winners: [],
};

export function gameReducer(state, event) {
    switch (event.type) {
        case NEW_STREET_EVENT:
            return {...state, street: event.payload.newStreet};
        case PLAYERS_UPDATE_EVENT:
            return {...state, players: event.payload.newPlayersList};
        case DEAL_PLAYERS_EVENT:
            return {...state, holeCards: event.payload.playerCardsList};
        case DEAL_BOARD_EVENT:
            return {...state, board: event.payload.communityCardsList};
        case NEXT_PLAYER_TO_ACT_EVENT:
            return {... state, nextPlayerToAct: event.payload.playerToActInfo};
        case NEW_PLAYER_ACTION_EVENT:
            return {...state, newPlayerAction: event.payload.playerActionInfo};
        case POT_UPDATE_EVENT:
            return {...state, pots: event.payload.updatedPotsList};
        case SHOWDOWN_EVENT:
            return {...state, showdownPlayers: event.payload.playersInHandList};
        case POT_WINNER_EVENT:
            return {...state, winners: event.payload.potWinnersList};
        case 'RESET_GAME':
            return initialState;
        default:
            return state;
    }
}