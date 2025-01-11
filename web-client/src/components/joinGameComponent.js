import React, { useState } from 'react';
import { joinGame } from '../grpc/UnaryCalls';
import { saveSessionTokenToLocalStore } from '../utils/LocalStorage';
import "../HomePageUI.css";

const JoinGameComponent = ({ dispatch, navigate }) => {
    const [playerName, setPlayerName] = useState('');
    const [chips, setChips] = useState(0);

    const handleJoinGame = async () => {
        try {
            const response = await joinGame(playerName, chips);
            console.log('Server Response:', response.serverMessage);

            if (response.success) {
                saveSessionTokenToLocalStore(response.playerId);
                console.log('New user registered. Navigating to the /game');
                navigate('/game');
            }
        } catch (error) {
            console.error('Join request rejected. Try again.', error);
        }
    };

    return (
        <div className="join-game-container">
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
                placeholder="Enter Chips (in BB)"
            />
            <button onClick={handleJoinGame}>Join Game</button>
        </div>
    );
};

export default JoinGameComponent;