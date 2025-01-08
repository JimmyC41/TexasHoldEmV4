import React from 'react';

const PotDisplay = ({ pots = [] }) => {
  if (!pots.length) return null;

  return (
    <div className="pot-display">
      {pots.map((pot, index) => {
        const potSize = pot.potChips || 0; 
        return (
          <div key={index} className="pot-line">
            Pot {index + 1}: {potSize} BB
          </div>
        );
      })}
    </div>
  );
};

export default PotDisplay;