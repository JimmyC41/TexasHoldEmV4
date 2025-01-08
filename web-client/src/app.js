import React from 'react';
import HomePage from './pages/HomePage';
import GamePage from './pages/GamePage';
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
