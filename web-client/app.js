// src/App.js
import React, { useState } from 'react';
import JoinGameComponent from './src/components/joinGameComponent';
import LeaveGameComponent from './src/components/leaveGameComponent';
import PlayerActionComponent from './src/components/playerActionComponent';
import SubscribeGameComponent from './src/components/subscribeComponent';
import GameStateDisplay from './src/components/gameStateDisplay';


const App = () => {
  const [playerId, setPlayerId] = useState('');

  const handleInputChange = (event) => {
    setPlayerId(event.target.value);  // Update playerId as the user types
  };

  return (
    <div>
      <h1>Texas Hold'em Poker Game</h1>

      <GameStateDisplay />

      {/* Join game component */}
      <JoinGameComponent />

      {/* Leave game component */}
      <LeaveGameComponent />

      {/* Player action component */}
      <PlayerActionComponent />

      {/* Subscribe to game events */}
      {!playerId ? (
        <div>
          <h3>Please enter your Player ID to subscribe to events</h3>
          <input
            type="text"
            placeholder="Enter Player ID"
            value={playerId}
            onChange={handleInputChange}
          />
        </div>
      ) : (
        <SubscribeGameComponent playerId={playerId} />
      )}
    </div>
  );
};

export default App;
