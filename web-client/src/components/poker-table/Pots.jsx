import React from 'react';
import '../../PokerUI.css';

const Pots = ({ pots = [] }) => {
  	if (!pots.length) return null;

  	return (
		<div className="pot-display">
	  		<div className="pot-box">
				{pots.map((pot, index) => {
		  			const potSize = pot.potChips || 0;
		  			return (
						<div key={index} className="pot-line">
			  				Pot: {potSize} BB
						</div>
		  			);
				})}
	 		</div>
		</div>
  	);
};

export default Pots;
