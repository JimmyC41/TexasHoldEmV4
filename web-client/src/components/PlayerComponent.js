import React from 'react';

const PlayerComponent = ({ player, isNextToAct }) => {
    const playerStyles = {
        display: 'flex',
        flexDirection: 'column',
        alignItems: 'center',
        padding: '10px',
        border: isNextToAct ? '2px solid gold' : '1px solid #ccc',
        borderRadius: '8px',
        backgroundColor: '#f9f9f9',
        width: '120px',
        textAlign: 'center',
    };
    
    return (
        <div style={playerStyles}>
            <div>{player.name}</div>
            <div>Chips: {player.chips}</div>
        </div>
    );
};

export default PlayerComponent;