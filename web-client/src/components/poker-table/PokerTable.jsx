// src/components/poker-table/PokerTable.jsx
import React, { useContext } from 'react';
import { GameContext } from '../../GameContext';
import Board from './Board';
import Pots from './Pots';
import LastAction from './LastAction';
import Players from './Players.jsx'


const PokerTable = () => {
  const { state } = useContext(GameContext);
  const { players, board, pots, newPlayerAction } = state;

  if (!players || players.length < 2) {
	return (
	  <div className="poker-table-container">
		<p className="waiting-text">Waiting for players to join...</p>
	  </div>
	);
  }

  return (
	<div className="poker-table-container">
	  <div
		className="table-background"
		style={{
		  background: 'url("/assets/poker-table.svg") center/contain no-repeat',
		  minHeight: '600px',
		  position: 'relative'
		}}>
		
		<Players players={players} />
		<Board cards={board} />
		<Pots pots={pots} />
		<LastAction
		  newPlayerAction={newPlayerAction}
		  players={players}
		/>
	  </div>
	</div>
  );
};

export default PokerTable;
