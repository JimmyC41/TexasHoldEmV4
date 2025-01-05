import React from 'react';
import { useSelector } from 'react-redux';

const GameStateDisplay = () => {
    const gameState = useSelector((state) => state);

    console.log(gameState);

    return (
        <div style ={{ whiteSpace: 'pre-wrap', fontFamily: 'monospace' }}>
            <h2>Game State</h2>
            <pre>{JSON.stringify(gameState, null, 2)}</pre>
        </div>
    );
};

export default GameStateDisplay;