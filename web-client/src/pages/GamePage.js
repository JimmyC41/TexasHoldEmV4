import React, { useContext } from 'react';
import useRedirectUser from '../hooks/UseRedirectUser'
import PlayerActionComponent from '../components/PlayerActionComponent';
import LeaveGameComponent from '../components/LeaveGameComponent';
import ManualResetGameComponent from '../components/ManualResetGameComponent'
import PokerTable from '../components/poker-table/PokerTable';
import '../PokerUI.css';

const GamePage = () => {
	useRedirectUser();

	return (
		<div className="game-page-container">
			<PokerTable />
			<div className="top-right-container">
				<LeaveGameComponent />
				<ManualResetGameComponent />
			</div>
			<div className="bottom-right-container">
				<PlayerActionComponent />
			</div>
		</div>
	);
};

export default GamePage;