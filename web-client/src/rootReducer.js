import { combineReducers } from 'redux';
import boardReducer from './reducers/boardReducer';
import holeCardsReducer from './reducers/holeCardsReducer';
import playerActionReducer from './reducers/playerActionReducer';
import playersReducer from './reducers/playersReducer';
import playerToActReducer from './reducers/playerToActReducer';
import potsReducer from './reducers/potsReducer';
import showdownReducer from './reducers/showdownReducer';
import streetReducer from './reducers/streetReducer'
import winnerReducer from './reducers/winnerReducer'

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