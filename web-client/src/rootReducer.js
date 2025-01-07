import { combineReducers } from 'redux';
import boardReducer from './reducers/BoardReducer';
import holeCardsReducer from './reducers/HoleCardsReducer';
import playerActionReducer from './reducers/PlayerActionReducer';
import playersReducer from './reducers/PlayersReducer';
import playerToActReducer from './reducers/PlayerToActReducer';
import potsReducer from './reducers/PotsReducer';
import showdownReducer from './reducers/ShowdownReducer';
import streetReducer from './reducers/StreetReducer'
import winnerReducer from './reducers/WinnerReducer'

const rootReducer = combineReducers({
    street: streetReducer,
    players: playersReducer,
    holeCards: holeCardsReducer,
    communityCards: boardReducer,
    nextPlayerToAct: playerToActReducer,
    lastAction: playerActionReducer,
    pots: potsReducer,
    playersInShowdown: showdownReducer,
    potWinners: winnerReducer,
});

export default rootReducer;