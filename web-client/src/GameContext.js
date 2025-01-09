import React, { createContext, useReducer, useEffect } from 'react';
import { gameReducer, initialState } from './GameReducer';
import { 
    loadStateFromLocalStorage,
    saveStateToLocalStorage,
    clearLocalStorage
} from './utils/LocalStorage';

// Context
export const GameContext = createContext();

// Provider encloses the App component to share states with individual components
const GameProvider = ({ children }) => {
    const [state, dispatch] = useReducer(gameReducer, loadStateFromLocalStorage());

    // Helper method to manual reset local storage in case of server disconnection
    const clearGameStateAndSession = () => {
        clearLocalStorage();
        dispatch({ type: 'RESET_GAME' }); 
    };

    // Save state to local storage whenever it changes
    useEffect(() => { saveStateToLocalStorage(state); }, [state]);

    return (
        <GameContext.Provider value={{ state, dispatch, clearGameStateAndSession }}>
            {children}
        </GameContext.Provider>
    );
};

export default GameProvider;