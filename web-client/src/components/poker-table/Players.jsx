import React from 'react';
import Seat from './Seat';
import { seatCoordinates, betCoordinates } from '../../utils/Coordinates';
import RecentBet from './RecentBet';
import '../../PokerUI.css';

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
							style={{ top: seatCoord.top, left: seatCoord.left, }}>
							Empty Seat
						</div>
					);
				}

				return (
					<div key={player.id}>
						<Seat
						player={player}
						style={{ top: seatCoord.top, left: seatCoord.left, }} />
						<RecentBet player={player} coordinates={betCoord} />
					</div>
				);
			})}
		</>
  	);
};

export default Players;
