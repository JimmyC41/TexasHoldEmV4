// src/components/poker-table/Seats.jsx
import React from 'react';
import Seat from './Seat';
import { seatCoordinates, betCoordinates } from '../../utils/Coordinates';
import RecentBet from './RecentBet';

const Players = ({ players }) => {
  	return (
		<>
	  	{Object.keys(seatCoordinates).map((posStr) => {
			const seatNumber = parseInt(posStr, 10);
			const seatCoord = seatCoordinates[seatNumber];
			const betCoord = betCoordinates[seatNumber];
			const player = players.find((p) => p.position === seatNumber);

			if (!player) {
		  		return (
					<div
			  			key={posStr}
			  			className="seat-container empty-seat"
			  			style={{
							top: seatCoord.top,
							left: seatCoord.left,
							transform: 'translate(-50%, -50%)'
			  			}}>
			  		Empty
					</div>
		  		);
			}

			return (
				<div>
					<Seat
					key={player.id}
					player={player}
					style={{
			  			position: 'absolute',
			  			top: seatCoord.top,
			  			left: seatCoord.left,
			  			transform: 'translate(-50%, -50%)'
					}}
		  			/>
					<RecentBet 
						player={player}
						coordinates={betCoord}
					/>
				</div>
			);
	  	})}
		</>
  	);
};

export default Players;
