import { combineReducers } from 'redux';
import boardReducer from './BoardReducer';
import holeCardsReducer from './HoleCardsReducer';
import playerActionReducer from './PlayerActionReducer';
import playersReducer from './PlayersReducer';
import playerToActReducer from './PlayerToActReducer';
import potsReducer from './PotsReducer';
import showdownReducer from './ShowdownReducer';
import streetReducer from './StreetReducer'
import winnerReducer from './WinnerReducer'

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