export const saveSessionTokenToLocalStore = (sessionToken) => {
    try {
        localStorage.setItem('sessionToken', sessionToken);
    } catch(e) {
        console.error("Could not save session token to local storage", e);
    }
};

export const loadSessionTokenFromLocalStorage = () => {
    try { 
        return localStorage.getItem('sessionToken');
    } catch (e) {
        console.error("Could not load session token from local storage", e);
        return null;
    }
};

export const saveStateToLocalStorage = (state) => {
    try {
        localStorage.setItem('gameState', JSON.stringify(state));
    } catch (err) {
        console.error('Failed to save state to local storage', err);
    }
};

export const loadStateFromLocalStorage = () => {
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