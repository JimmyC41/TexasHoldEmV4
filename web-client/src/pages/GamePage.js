import React, { useContext } from 'react';
import { GameContext } from '../GameContext';
import { useNavigate } from 'react-router-dom';
import useRedirectUser from '../hooks/UseRedirectUser'
import PlayerActionComponent from '../components/PlayerActionComponent';
import LeaveGameComponent from '../components/LeaveGameComponent';
import ManualResetGameComponent from '../components/ManualResetGameComponent'
import PokerTable from '../components/poker-table/PokerTable';
import JoinGameComponent from '../components/JoinGameComponent';

const GamePage = () => {
    const { dispatch } = useContext(GameContext);
    const navigate = useNavigate();

    useRedirectUser();

    return (
        <div>
            <PokerTable />
            <JoinGameComponent dispatch={dispatch} navigate={navigate} />
            <PlayerActionComponent />
            <LeaveGameComponent />
            <ManualResetGameComponent />
        </div>
    );
};

export default GamePage;