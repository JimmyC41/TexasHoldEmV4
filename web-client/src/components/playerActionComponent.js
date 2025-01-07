import React, { useState } from 'react';
import { playerAction } from '../grpc/UnaryCalls';

const PlayerActionComponent = () => {
	const [playerId, setPlayerId] = useState('');
	const [actionType, setActionType] = useState(0);
	const [amount, setAmount] = useState(0);
	
	const handlePlayerAction = async () => {
		try {
			const response = await playerAction(playerId, actionType, amount);
			console.log('Server response: ', response.serverMessage);
		} catch (error) {
		console.error('Action request rejected. Try again.');
		}
	};

	return (
		<div>
			<h3>Player Action</h3>
			<input
				type="text"
				value={playerId}
				onChange={(e) => setPlayerId(e.target.value)}
				placeholder="PlayerId or Name?"
			/>
			<input
				type="number"
				value={actionType}
				onChange={(e) => setActionType(parseInt(e.target.value, 10))}
				placeholder="Enter Action Enum"
			/>
			<input
				type="number"
				value={amount}
				onChange={(e) => setAmount(parseInt(e.target.value, 10))}
				placeholder="Enter Amount"
			/>
			<button onClick={handlePlayerAction}>Perform Action</button>
		</div>
	);
};

export default PlayerActionComponent;
