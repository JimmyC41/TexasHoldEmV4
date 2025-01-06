import React, { useEffect } from 'react';
import { useDispatch, useSelector } from 'react-redux';
import { useNavigate } from 'react-router-dom';
import { loadSessionTokenFromLocalStorage } from '../utils/localStorage';
import PlayerActionComponent from './playerActionComponent';
import { gameStream } from '../grpc/streamingCalls';

const GamePage = () => {
    const dispatch = useDispatch();
    const navigate = useNavigate();
    const gameState = useSelector((state) => state);
    const sessionToken = loadSessionTokenFromLocalStorage();

    console.log(gameState);

    useEffect(() => {
        // For first time login, redirect to the Join Game page
        if (!sessionToken) {
            navigate('/');
            return;
        }

        // If session token exists, load previous game state and re-subscribe
        const stream = gameStream(sessionToken, dispatch);

        return () => {
            if (stream) stream.cancel();
        };
    
    },  [sessionToken, dispatch, navigate]);

    return (
        <div>
            <h2>Game In Progress</h2>
            <pre>{JSON.stringify(gameState, null, 2)}</pre>
            <PlayerActionComponent />
        </div>
    );
};

export default GamePage;