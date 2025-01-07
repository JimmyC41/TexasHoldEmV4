import React, { createContext, useReducer, useEffect } from 'react';
import { gameReducer, initialState } from './GameReducer';

// Context
export const GameContext = createContext();

// Save state to local storage
const saveStateToLocalStorage = (state) => {
    try {
        localStorage.setItem('gameState', JSON.stringify(state));
    } catch (err) {
        console.error('Failed to save state to local storage', err);
    }
};

// Load state from local storage
const loadStateFromLocalStorage = () => {
    try {
        const storedState = localStorage.getItem('gameState');
        if (!storedState) {
            return initialState;
        }
        return JSON.parse(storedState);
    } catch (err) {
        console.error('Failed to load state from local storage', err);
        return initialState
    }
};

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