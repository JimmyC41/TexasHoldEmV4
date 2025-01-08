import React from 'react';

const RecentBet = ({ player, coordinates }) => {
  	if (!player || player.recentBets <= 0) return null;

  	return (
		<div
	  		className="bet-display"
	  		style={{
				position: 'absolute',
				top: coordinates.top,
				left: coordinates.left,
				transform: 'translate(-50%, -50%)',
	  		}}>
	  		{player.recentBets} BB
		</div>
  	);
};

export default RecentBet;
