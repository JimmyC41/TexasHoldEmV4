import React from 'react';
import { getCardImagePath } from '../../utils/CardHelpers';

const Card = ({ card, faceUp }) => {
  if (!card) return null;

  if (!faceUp) {
    return (
      <img
        src="/assets/cards/back_card.svg" 
        alt="Card back"
        style={{ width: '40px' }}
      />
    );
  }

  const imagePath = getCardImagePath(card.suit, card.value);

  return (
    <img
      src={imagePath}
      alt="Card"
      style={{ width: '40px' }}
    />
  );
};

export default Card;
