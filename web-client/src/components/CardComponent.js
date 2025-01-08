import React from 'react';
import { SUIT, VALUE } from '../Enum';
import '../styles.css';

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

const CardComponent = ({ suit, value }) => {
    return (
        <div className="card-small">
            <div className="value">{value}</div>
            <div> className="suit"{suit}</div>
        </div>
    )
};

export default CardComponent;