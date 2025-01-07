import React from 'react';
import ReactDOM from 'react-dom/client';
import App from './app';
import { GameProvider } from './GameContext';

const root = ReactDOM.createRoot(document.getElementById('root'));
root.render(
    <GameProvider>
        <App />
    </GameProvider>
);