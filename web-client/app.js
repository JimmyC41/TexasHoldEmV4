// src/App.js
import React, { useState } from 'react';
import JoinGameComponent from './src/components/joinGameComponent';
import LeaveGameComponent from './src/components/leaveGameComponent';
import PlayerActionComponent from './src/components/playerActionComponent';
import GameStateDisplay from './src/components/gameStateDisplay';


const App = () => {
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
    </div>
  );
};

export default App;
