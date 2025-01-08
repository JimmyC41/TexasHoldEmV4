import React, { useContext } from 'react';
import { GameContext } from '../GameContext';
import useRedirectUser from '../hooks/UseRedirectUser'
import PlayerActionComponent from '../components/PlayerActionComponent';
import LeaveGameComponent from '../components/LeaveGameComponent';
import ManualResetGameComponent from '../components/ManualResetGameComponent'

const GamePage = () => {
    const { state } = useContext(GameContext);

    // Redirects new players to the game page
    useRedirectUser();

    return (
        <div>
            <pre>{JSON.stringify(state, null, 2)}</pre>
            <PlayerActionComponent />
            <LeaveGameComponent />
            <ManualResetGameComponent />
        </div>
    );
};

export default GamePage;