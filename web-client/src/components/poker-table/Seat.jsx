// src/components/PokerTable/Seat.jsx

import React, { useContext } from 'react';
import { GameContext } from '../../GameContext';
import Card from './Card';

const Seat = ({ player, style }) => {
    const { state } = useContext(GameContext);
    const sessionToken = localStorage.getItem('sessionToken');
  
    const isLocalPlayer = (player.id === sessionToken);
    const isFolded = (player.status === 2);
    const isNextToAct = (state.nextPlayerToAct?.playerToAct === player.id);

    const seatClassName = [
        'seat-container',
        isFolded ? 'folded' : '',
        isNextToAct ? 'highlight' : '',
    ].join(' ');

    const holeCardsEntry = state.holeCards.find(hc => hc.playerId === player.id);
    const holeCards = holeCardsEntry ? holeCardsEntry.holeCardsList : [];

    return (
        <div className={seatClassName} style={style}>
            <div className="player-info">
                <div className="player-name">{player.name}</div>
                <div className="player-chips">{player.chips} BB</div>
            </div>

            <div className="hole-cards">
                {holeCards.map((card, i) => (
                <Card key={i} card={card} faceUp={isLocalPlayer} /> 
                ))}
            </div>
        </div>
    );
};

export default Seat;
