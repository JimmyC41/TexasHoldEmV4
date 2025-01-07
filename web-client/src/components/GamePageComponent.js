import React, { useEffect, useContext } from 'react';
import { useNavigate } from 'react-router-dom';
import { GameContext } from '../GameContext';
import { loadSessionTokenFromLocalStorage } from '../utils/LocalStorage';
import { gameStream } from '../grpc/StreamingCalls';
import PlayerActionComponent from './PlayerActionComponent';
import LeaveGameComponent from './LeaveGameComponent';

const GamePageComponent = () => {
    const { state, dispatch } = useContext(GameContext);
    const navigate = useNavigate();
    const sessionToken = loadSessionTokenFromLocalStorage();
    
    useEffect(() => {
        if (!sessionToken) {
            navigate('/');
        }
        else {
            const stream = gameStream(sessionToken, dispatch);
            return () => stream.cancel();
        }
    }, [sessionToken, dispatch, navigate]);

    return (
        <div>
            <h2>Game In Progress</h2>
            <pre>{JSON.stringify(state, null, 2)}</pre>

            <h2>Enter Your Action Here</h2>
            <PlayerActionComponent />
            <LeaveGameComponent />
        </div>
    );
};

export default GamePageComponent;