// BoardComponent.js
import React, { useState, useEffect, useRef } from 'react';
import CardComponent from './CardComponent';

const boardStyles = {
    display: 'flex',
    justifyContent: 'center',
    alignItems: 'center',
    gap: '10px',
};

const BoardComponent = ({ board }) => {
    const boardRef = useRef(null);
    const [boardSize, setBoardSize] = useState({ width: 0, height: 0 });

    useEffect(() => {
        if (boardRef.current) {
            const { width, height } = boardRef.current.getBoundingClientRect();
            setBoardSize({ width, height });
        }
    }, [board]);

    return (
        <div ref={boardRef} style={boardStyles}>
            {board && board.length > 0 ? (
                board.map((card, index) => (
                    <CardComponent
                        key={index}
                        suit={card.suit}
                        value={card.value}
                        boardSize={boardSize}
                    />
                ))
            ) : (
                <span>No cards to display</span>
            )}
        </div>
    );
};

export default BoardComponent;
