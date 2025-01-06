import React, { useState } from 'react';
import { leaveGame } from '../grpc/unaryCalls';

const LeaveGameComponent = () => {
  const [playerName, setPlayerName] = useState('');

  const handleLeaveGame = async () => {
    try {
      const response = await leaveGame(playerName);
      console.log('Server response: ', response.serverMessage);
    } catch {
      console.error('Request rejected by the server. Try again.');
    }
  };

  return (
    <div>
      <h3>Leave Game</h3>
      <input
        type="text"
        value={playerName}
        onChange={(e) => setPlayerName(e.target.value)}
        placeholder="Enter your name"
      />
      <button onClick={handleLeaveGame}>Leave Game</button>
    </div>
  );
};

export default LeaveGameComponent;
