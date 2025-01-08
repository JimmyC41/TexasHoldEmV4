import React, { useContext } from 'react';
import { GameContext } from '../GameContext';
import useJoinGame from '../hooks/useJoinGame'
import PlayerActionComponent from './PlayerActionComponent';
import LeaveGameComponent from './LeaveGameComponent';

const GamePageComponent = () => {
    const { state } = useContext(GameContext);
    useJoinGame();

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