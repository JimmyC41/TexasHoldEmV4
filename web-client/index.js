import React from 'react';
import ReactDOM from 'react-dom/client';
import { Provider } from 'react-redux';
import store from './src/store/store';
import GameStateDisplay from './src/components/gameStateDisplay';
import App from './app';


import { gameStream, joinGame, playerAction } from './src/api/grpc';

const delay = (ms) => new Promise(resolve => setTimeout(resolve, ms));

// Render the React app
const root = ReactDOM.createRoot(document.getElementById('root'));
root.render(
    <Provider store={store}>  // Make the store available to the entire app
        <App />
    </Provider>
);