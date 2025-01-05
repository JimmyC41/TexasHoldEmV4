import { DEAL_PLAYERS_EVENT } from "../events/gameEvents";

const holeCardsReducer = (state = initialState, gameEvent) => {
    switch (gameEvent.type) {
        case DEAL_PLAYERS_EVENT:
            return {
                ...state,
                players: state.players.map(player => {
                    const update = gameEvent.payload.find(update => update.id === player.id);
                    if (update) {
                        return { ...player, ...holeCards.update.holeCards };
                    }
                    return player;
                })
            };
        default:
            return state;
    }
}

export default holeCardsReducer;