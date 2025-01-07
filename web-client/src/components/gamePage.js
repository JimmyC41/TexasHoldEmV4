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
            navigate('/');
        } catch {
            console.error('Request rejected by the server. Try again.');
        }
    };

    return (
        <div>
            <h2>Game In Progress</h2>
            <pre>{JSON.stringify(gameState, null, 2)}</pre>
            <PlayerActionComponent />
        </div>
    );
};

export default GamePage;