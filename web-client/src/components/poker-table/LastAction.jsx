import React from 'react';

const actionTypeMap = {
  	0:  'Unspecified',
  	1:  'Posts SB',
  	2:  'Posts BB',
  	3:  'Checks',
  	4:  'Bets',
  	5:  'Calls',
  	6:  'Raises',
  	7:  'Folds',
  	8:  'All-in (Bet)',
  	9:  'All-in (Call)',
  	10: 'All-in (Raise)'
};

const LastActionBox = ({ newPlayerAction, players }) => {
  	if (!newPlayerAction || !newPlayerAction.action) {
    	return null;
  	}

  	const { playerId, action } = newPlayerAction;
  	if (!playerId || !action) {
    	return null;
  	}

  	const player = players.find((p) => p.id === playerId);
  	if (!player) {
    	return null;
  	}

  	const { actionType, actionAmount } = action;
  	const actionText = actionTypeMap[actionType] || 'Unknown Action';

  	let displayString = `${player.name} ${actionText}`;
  	if (actionAmount && actionAmount > 0) {
    	displayString += ` ${actionAmount}`;
  	}

  	return (
    	<div className="last-action-box">
      	{displayString}
    	</div>
  	);
};

export default LastActionBox;
