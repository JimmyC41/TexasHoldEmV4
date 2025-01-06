import React, { useState } from 'react';
import { joinGame } from '../grpc/unaryCalls';
import { gameStream } from '../grpc/streamingCalls';
import { useDispatch } from 'react-redux';

const JoinGameComponent = () => {
  const dispatch = useDispatch();
  const [playerName, setPlayerName] = useState('');
  const [chips, setChips] = useState(0);
  const [stream, setStream] = useState(null);
  const [errorMessage, setErrorMessage] = useState('');

  const handleJoinGame = async () => {
    try {
      const response = await joinGame(playerName, chips);
      if (response.success) {
        console.log(response.message);
        const newStream = gameStream(playerName, dispatch);
        setStream(newStream);
      }
      else {
        setErrorMessage(response.message);
      }
    } catch (error) {
      console.error(error);
      setErrorMessage('An unexpected error occured. Try again.');
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
