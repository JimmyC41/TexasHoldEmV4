import React, { createContext, useReducer, useEffect } from 'react';
import { gameReducer, initialState } from './GameReducer';
import { 
    loadStateFromLocalStorage,
    saveStateToLocalStorage 
} from './utils/LocalStorage';

// Context
export const GameContext = createContext();

// Provider Component
const GameProvider = ({ children }) => {
    const [state, dispatch] = useReducer(gameReducer, loadStateFromLocalStorage());

    // Clear the game state and session data from local storage
    const clearGameStateAndSession = () => {
        try {
            localStorage.removeItem('gameState');
            localStorage.removeItem('sessionToken');
            dispatch({ type: 'RESET_GAME' });
        } catch (err) {
            console.error('Error clearing local storage', err);
        }
    };

    // Save state to local storage whenever it changes
    useEffect(() => {
        saveStateToLocalStorage(state);
    }, [state]);

    return (
        <GameContext.Provider value={{ state, dispatch, clearGameStateAndSession }}>
            {children}
        </GameContext.Provider>
    );
};

export default GameProvider;