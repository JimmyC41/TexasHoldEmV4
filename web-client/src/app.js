// App.js: Entry for the application, handles routing

import React, { useState } from 'react';
import JoinGameComponent from './components/joinGameComponent';
import LeaveGameComponent from './components/leaveGameComponent';
import PlayerActionComponent from './components/playerActionComponent';
import GameStateDisplay from './components/gameStateDisplay';

const App = () => {
	const [sessionToken, setSessionToken] = useState(localStorage.getItem('sessionToken') || '');
	
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
