import React, { useState } from 'react';
import { joinGame } from '../grpc/UnaryCalls';
import { gameStream } from '../grpc/StreamingCalls';
import { useDispatch } from 'react-redux';
import { useNavigate } from 'react-router-dom';
import { loadSessionTokenFromLocalStorage, saveSessionTokenToLocalStore } from '../utils/LocalStorage';

const JoinGameComponent = () => {
  	const dispatch = useDispatch();
  	const navigate = useNavigate();
    const sessionToken = loadSessionTokenFromLocalStorage();
  	const [playerName, setPlayerName] = useState('');
  	const [chips, setChips] = useState(0);

  	const handleJoinGame = async () => {
    	try {
      		const response = await joinGame(playerName, chips);
      		console.log('Server response: ', response.serverMessage);

      		if (response.success) {
        		saveSessionTokenToLocalStore(response.playerId);
        		const newStream = gameStream(response.playerId, dispatch);
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
