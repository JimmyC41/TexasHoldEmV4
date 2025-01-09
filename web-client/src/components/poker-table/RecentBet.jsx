import React from 'react';
import '../../PokerUI.css';

const RecentBet = ({ player, coordinates }) => {
  	if (!player || player.recentBets <= 0) return null;

  	return (
		<div
	  		className="bet-display"
	  		style={{ top: coordinates.top, left: coordinates.left, }}>
	  		{player.recentBets} BB
		</div>
  	);
};

export default RecentBet;
