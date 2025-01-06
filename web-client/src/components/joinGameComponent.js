import React, { useState } from 'react';
import { joinGame } from '../grpc/unaryCalls';
import { gameStream } from '../grpc/streamingCalls';
import { useDispatch } from 'react-redux';
import { useNavigate } from 'react-router-dom';
import { saveSessionTokenToLocalStore } from '../utils/localStorage';

const JoinGameComponent = () => {
  const dispatch = useDispatch();
  const navigate = useNavigate();
  const [playerName, setPlayerName] = useState('');
  const [chips, setChips] = useState(0);
  const [stream, setStream] = useState(null);

  const handleJoinGame = async () => {
    try {
      const response = await joinGame(playerName, chips);
      console.log('Server response: ', response.serverMessage);

      if (response.success) {
        saveSessionTokenToLocalStore(response.playerId);
        const newStream = gameStream(response.playerId, dispatch);
        setStream(newStream);
        navigate('/game');
      }
    } catch {
      console.error('Request rejected by the server. Try again.');
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
    </div>
  );
};

export default JoinGameComponent;
