import { useEffect, useContext } from 'react';
import { useNavigate } from 'react-router-dom';
import { GameContext } from '../GameContext';
import { loadSessionTokenFromLocalStorage } from '../utils/LocalStorage';
import { gameStream } from '../grpc/StreamingCalls';

const useRedirectUser = () => {
    const { dispatch } = useContext(GameContext);
    const navigate = useNavigate();
    const sessionToken = loadSessionTokenFromLocalStorage();

    useEffect(() => {
        if (!sessionToken) {
            navigate('/');
        } else {
            // If the session token exists, then exisitng user
            // Subscribe the user to the game stream
            const stream = gameStream(sessionToken, dispatch);
            navigate('/game')
            return () => stream.cancel();
        }
    }, [sessionToken, dispatch, navigate]);
};

export default useRedirectUser;