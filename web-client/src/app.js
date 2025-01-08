import React from 'react';
import HomePage from './components/HomePage';
import GamePage from './components/GamePage';
import { BrowserRouter as Router, Route, Routes } from 'react-router-dom';

const App = () => {	
  return (
    <Router>
      <Routes>
        <Route path="/" element={<HomePage />} />
        <Route path="/game" element={<GamePage />} />
      </Routes>
    </Router>
  );
};

export default App;
