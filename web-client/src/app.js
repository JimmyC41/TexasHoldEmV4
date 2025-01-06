// App.js: Entry for the application, handles routing

import React from 'react';
import JoinGameComponent from './components/joinGameComponent';
import GamePage from './components/gamePage';
import { BrowserRouter as Router, Route, Routes } from 'react-router-dom';

const App = () => {	
  return (
    <Router>
      <Routes>
        <Route path="/" element={<JoinGameComponent />} />
        <Route path="/game" element={<GamePage />} />
      </Routes>
    </Router>
  );
};

export default App;
