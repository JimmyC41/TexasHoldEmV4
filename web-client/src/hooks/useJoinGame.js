import { useEffect, useContext } from 'react';
import { useNavigate } from 'react-router-dom';
import { GameContext } from '../GameContext';
import { loadSessionTokenFromLocalStorage } from '../utils/LocalStorage';
import { gameStream } from '../grpc/StreamingCalls';

const useJoinGame = () => {
    const { dispatch } = useContext(GameContext);
    const navigate = useNavigate();
    const sessionToken = loadSessionTokenFromLocalStorage();

    useEffect(() => {
        if (!sessionToken) {
            navigate('/');
        } else {
            const stream = gameStream(sessionToken, dispatch);
            navigate('/game')
            return () => stream.cancel();
        }
    }, [sessionToken, dispatch, navigate]);
};

export default useJoinGame;