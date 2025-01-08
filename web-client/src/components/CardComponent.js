// CardComponent.js
import React from 'react';
import { SUIT, VALUE } from '../Enum';

const suitSymbols = {
    [SUIT.HEARTS]: '\u2665',
    [SUIT.DIAMONDS]: '\u2666',
    [SUIT.CLUBS]: '\u2663',
    [SUIT.SPADES]: '\u2660',
};

const suitColors = {
    [SUIT.HEARTS]: 'red',
    [SUIT.DIAMONDS]: 'red',
    [SUIT.CLUBS]: 'black',
    [SUIT.SPADES]: 'black',
};

const valueSymbols = {
    [VALUE.TWO]: '2',
    [VALUE.THREE]: '3',
    [VALUE.FOUR]: '4',
    [VALUE.FIVE]: '5',
    [VALUE.SIX]: '6',
    [VALUE.SEVEN]: '7',
    [VALUE.EIGHT]: '8',
    [VALUE.NINE]: '9',
    [VALUE.TEN]: '10',
    [VALUE.JACK]: 'J',
    [VALUE.QUEEN]: 'Q',
    [VALUE.KING]: 'K',
    [VALUE.ACE]: 'A',
};

const CardComponent = ({ suit, value, boardSize }) => {
    const cardWidth = boardSize.width > 0 ? boardSize.width * 0.25 : 100;
    const cardHeight = boardSize.height > 0 ? boardSize.height * 0.6 : 200;

    const color = suitColors[suit];

    const cardStyles = {
        width: `${cardWidth}px`,
        height: `${cardHeight}px`,
        border: '1px solid #ccc',
        borderRadius: '8px',
        display: 'flex',
        flexDirection: 'column',
        alignItems: 'center',
        justifyContent: 'center',
        backgroundColor: '#fff',
        boxShadow: '0 4px 8px rgba(0, 0, 0, 0.1)',
        fontFamily: 'Arial, sans-serif',
        fontSize: `${Math.min(cardWidth, cardHeight) * 0.3}px`,
        display: 'flex',
        justifyContent: 'center',
        alignItems: 'center',
    };

    return (
        <div style={cardStyles}>
            <div style={{ color: color }}>
                {valueSymbols[value]}
            </div>
            <div style={{ color: color, fontSize: '2.5vw' }}>
                {suitSymbols[suit]}
            </div>
        </div>
    );
};

export default CardComponent;
