// PlayerComponent.js
import React from 'react';

const PlayerComponent = ({ player, isNextToAct, isDealer }) => {
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
            {isDealer && <div style={dealerButtonStyle}>D</div>}
            <div>Chips: {player.chips}</div>
            <div>Recent Bet: {player.recentBets}</div>
        </div>
    );
};

const dealerButtonStyle = {
    backgroundColor: 'gold',
    color: 'black',
    fontWeight: 'bold',
    borderRadius: '50%',
    padding: '5px',
    marginBottom: '5px',
};

export default PlayerComponent;
