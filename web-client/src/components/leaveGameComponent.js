import React, { useState } from 'react';
import { leaveGame } from '../grpc/unaryCalls';

const LeaveGameComponent = () => {
  const [playerName, setPlayerName] = useState('');
  const [errorMessage, setErrorMessage] = useState('');

  const handleLeaveGame = async () => {
    try {
      const response = await leaveGame(playerName);
      if (response.success) {
        console.log('Player left the game successfully:', response.message);
      } else {
        setErrorMessage(response.message);  // Show error message if leaving fails
      }
    } catch (error) {
      console.error('Error leaving game:', error);
      setErrorMessage('Failed to leave the game');
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
      {errorMessage && <p style={{ color: 'red' }}>{errorMessage}</p>}
    </div>
  );
};

export default LeaveGameComponent;
