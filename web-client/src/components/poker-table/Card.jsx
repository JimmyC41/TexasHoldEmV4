import React from 'react';
import { getCardImagePath } from '../../utils/CardHelpers';
import '../../PokerUI.css';

const Card = ({ card, faceUp }) => {
  	if (!card) return null;

  	if (!faceUp) {
    	return (
      		<img
				className="card-img"
				src="/assets/cards/back_card.svg"
        		alt="Card back"
      		/>
    	);
  	}

  	const imagePath = getCardImagePath(card.suit, card.value);
  	return (
    	<img
			className="card-img"
      		src={imagePath}
      		alt="Card"
    	/>
  	);
};

export default Card;
