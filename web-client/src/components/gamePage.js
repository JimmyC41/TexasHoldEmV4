import React, { useEffect } from 'react';
import { useDispatch, useSelector } from 'react-redux';
import { useNavigate } from 'react-router-dom';
import { loadSessionTokenFromLocalStorage } from '../utils/LocalStorage';
import PlayerActionComponent from './PlayerActionComponent';
import { resetGameState } from '../grpc/GameEvents';
import { leaveGame } from '../grpc/UnaryCalls';

const GamePage = () => {
    const dispatch = useDispatch();
    const navigate = useNavigate();
    const gameState = useSelector((state) => state);
    const sessionToken = loadSessionTokenFromLocalStorage();

    // Handle leave game functionality
    const handleLeaveGame = async () => {
        try {
            const response = await leaveGame(sessionToken);
            console.log('Server response: ', response.serverMessage);

            dispatch(resetGameState());
            navigate('/');
        } catch {
            console.error('Request rejected by the server. Try again.');
        }
    };

    // Effect to handle browser unload (for refresh/close detection)
    const handleBeforeUnload = (event) => {
        event.preventDefault();
        event.returnValue = 'Are you sure you want to leave the game?';
        handleLeaveGame();
    }


    useEffect(() => {
        window.addEventListener('beforeunload', handleBeforeUnload);
        
        return () => {
            window.removeEventListener('beforeunload', handleBeforeUnload);
        };
    },  []);

    return (
        <div>
            <h2>Game In Progress</h2>
            <pre>{JSON.stringify(gameState, null, 2)}</pre>
            <PlayerActionComponent />
        </div>
    );
};

export default GamePage;