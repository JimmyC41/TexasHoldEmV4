import React, { useContext } from 'react';
import { GameContext } from '../GameContext';
import useRedirectUser from '../hooks/UseRedirectUser'
import PlayerActionComponent from '../components/PlayerActionComponent';
import LeaveGameComponent from '../components/LeaveGameComponent';
import ManualResetGameComponent from '../components/ManualResetGameComponent'
import Card from '../components/poker-table/Card';
import Board from '../components/poker-table/Board';
import Pot from '../components/poker-table/Pot';
import LastActionBox from '../components/poker-table/LastAction';
import Seat from '../components/poker-table/Seat';

const GamePage = () => {
    const { state } = useContext(GameContext);

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