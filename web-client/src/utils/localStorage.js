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