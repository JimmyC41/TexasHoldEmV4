import React, { useState, useContext } from 'react';
import { joinGame } from '../grpc/UnaryCalls';
import { gameStream } from '../grpc/StreamingCalls';
import { useNavigate } from 'react-router-dom';
import { saveSessionTokenToLocalStore } from '../utils/LocalStorage';
import { GameContext } from '../GameContext';
import useJoinGame from '../hooks/useJoinGame';

const JoinGameComponent = () => {
    const { dispatch } = useContext(GameContext);
  	const navigate = useNavigate();
  	const [playerName, setPlayerName] = useState('');
  	const [chips, setChips] = useState(0);

    useJoinGame();

  	const handleJoinGame = async () => {
    	try {
      		const response = await joinGame(playerName, chips);
      		console.log('Server response: ', response.serverMessage);

      		if (response.success) {
        		saveSessionTokenToLocalStore(response.playerId);
        		gameStream(response.playerId, dispatch);
				  console.log('Navigating to /game');
        		navigate('/game');
      		}
    	} catch {
      		console.error('Join request rejected. Try again.');
   		}
  };

  return (
    <div>
      <h3>Join Game</h3>
      <input
        type="text"
        value={playerName}
        onChange={(e) => setPlayerName(e.target.value)}
        placeholder="Enter Name"
      />
      <input
        type="number"
        value={chips}
        onChange={(e) => setChips(parseInt(e.target.value, 10))}
        placeholder="Enter Chips"
      />
      <button onClick={handleJoinGame}>Join Game</button>
    </div>
  );
};

export default JoinGameComponent;
