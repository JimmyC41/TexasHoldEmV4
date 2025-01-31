import React from 'react';
import Card from './Card';
import '../../PokerUI.css';

const Board = ({ cards = [] }) => {
	return (
		<div className="board-container">
			{cards.map((card, idx) => (
				<Card key={idx} card={card} faceUp={true} />
			))}
		</div>
	);
};

export default Board;
