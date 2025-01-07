import React from 'react';
import JoinGameComponent from './components/JoinGameComponent';
import GamePageComponent from './components/GamePageComponent';
import { BrowserRouter as Router, Route, Routes } from 'react-router-dom';

const App = () => {	
  return (
    <Router>
      <Routes>
        console.log(JoinGameComponent);
        console.log(GamePageComponent);
        <Route path="/" element={<JoinGameComponent />} />
        <Route path="/game" element={<GamePageComponent />} />
      </Routes>
    </Router>
  );
};

export default App;
