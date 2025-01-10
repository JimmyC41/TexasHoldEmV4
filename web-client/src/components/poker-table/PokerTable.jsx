import React, { useContext } from 'react';
import { GameContext } from '../../GameContext';
import Board from './Board';
import Pots from './Pots';
import LastAction from './LastAction';
import Players from './Players.jsx'
import '../../PokerUI.css';


const PokerTable = () => {
  	const { state } = useContext(GameContext);
  	const { players, board, pots, newPlayerAction } = state;

  	if (!players || players.length < 2) {
		return (
	  		<div className="poker-table-container">
				<p className="waiting-text">Waiting for another player to join the game...</p>
	  		</div>
		);
  	}

  	return (
		<div className="poker-table-container">
			<LastAction newPlayerAction={newPlayerAction} players={players} />

	  		<div className="table-background">
				<Players players={players} />
				<Board cards={board} />
				<Pots pots={pots} />
	  		</div>
		</div>
  	);
};

export default PokerTable;
