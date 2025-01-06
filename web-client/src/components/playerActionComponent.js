import React, { useState } from 'react';
import { playerAction } from '../grpc/unaryCalls';

const PlayerActionComponent = () => {
  const [playerId, setPlayerId] = useState('');
  const [actionType, setActionType] = useState('');
  const [amount, setAmount] = useState(0);

  const handlePlayerAction = async () => {
    try {
      const response = await playerAction(playerId, actionType, amount);
	  console.log('Server response: ', response.serverMessage);
    } catch (error) {
		console.error('Request rejected by the server. Try again.');
    }
  };

  return (
    <div>
      <h3>Player Action</h3>
      <input
        type="text"
        value={playerId}
        onChange={(e) => setPlayerId(e.target.value)}
        placeholder="Enter player ID"
      />
      <input
        type="number"
        value={actionType}
        onChange={(e) => setActionType(e.target.value)}
        placeholder="Enter action (RAISE, CALL, CHECK)"
      />
      <input
        type="number"
        value={amount}
        onChange={(e) => setAmount(parseInt(e.target.value, 10))}
        placeholder="Enter amount"
      />
      <button onClick={handlePlayerAction}>Perform Action</button>
    </div>
  );
};

export default PlayerActionComponent;
