import React, { useContext } from 'react';
import { GameContext } from '../GameContext';
import useRedirectUser from '../hooks/UseRedirectUser'
import TableComponent from './TableComponent';
import PlayerActionComponent from './PlayerActionComponent';
import LeaveGameComponent from './LeaveGameComponent';
import ManualResetGameComponent from './ManualResetGameComponent'

const GamePage = () => {
    const { state } = useContext(GameContext);

    // Redirects new players to the game page
    useRedirectUser();

    return (
        <div>
            <pre>{JSON.stringify(state, null, 2)}</pre>
            <TableComponent board={state.board || []} />
            <PlayerActionComponent />
            <LeaveGameComponent />
            <ManualResetGameComponent />
        </div>
    );
};

export default GamePage;