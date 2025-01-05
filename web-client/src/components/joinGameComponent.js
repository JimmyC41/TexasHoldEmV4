import React, { useState } from 'react';
import { useDispatch } from 'react-redux';
import { joinGame } from '../api/grpc';  // Import the joinGame method
import { playersUpdateEvent } from '../events/gameEvents';  // Import actions

const JoinGameComponent = () => {
  const [playerName, setPlayerName] = useState('');
  const [chips, setChips] = useState(0);
  const [errorMessage, setErrorMessage] = useState('');
  const dispatch = useDispatch();

  const handleJoinGame = async () => {
    try {
      const response = await joinGame(playerName, chips);
      if (response.success) {
        console.log('Player joined successfully:', response.message);
      } else {
        setErrorMessage(response.message);  // Show error message if join fails
      }
    } catch (error) {
      console.error('Error joining game:', error);
      setErrorMessage('Failed to join the game');
    }
  };

  return (
    <div>
      <h3>Join Game</h3>
      <input
        type="text"
        value={playerName}
        onChange={(e) => setPlayerName(e.target.value)}
        placeholder="Enter your name"
      />
      <input
        type="number"
        value={chips}
        onChange={(e) => setChips(parseInt(e.target.value, 10))}
        placeholder="Enter chips"
      />
      <button onClick={handleJoinGame}>Join Game</button>
      {errorMessage && <p style={{ color: 'red' }}>{errorMessage}</p>}
    </div>
  );
};

export default JoinGameComponent;
