import React, { useState, useContext } from 'react';
import { GameContext } from '../GameContext';
import { playerAction } from '../grpc/UnaryCalls';
import { loadSessionTokenFromLocalStorage } from '../utils/LocalStorage'
import { ACTION_TYPE } from '..//Enum';

const PlayerActionComponent = () => {
    const { state } = useContext(GameContext);
    const sessionToken = loadSessionTokenFromLocalStorage();
    const nextPlayerToAct = state?.nextPlayerToAct;

    const [betAmount, setBetAmount] = useState(0);

    if (!nextPlayerToAct || sessionToken !== nextPlayerToAct.playerToAct) {
        return null;
    }

    const handlePlayerAction = async (actionType, amount) => {
        try {
            const response = await playerAction(sessionToken, actionType, amount);
            console.log('Server response: ', response.serverMessage);
        } catch (error) {
            console.error('Action request rejected. Try again.');
        }
    };

    const renderActionButton = (action) => {
        const actionLabel = Object.keys(ACTION_TYPE).find(
            (key) => ACTION_TYPE[key] === action.actionType
        );
        const { primaryAmount, secondaryAmount } = action;

        if (primaryAmount === 0 && secondaryAmount === 0) {
            return (
                <button
                    key={action.actionType}
                    onClick={() => handlePlayerAction(action.actionType, 0)}>
                    {actionLabel}
                </button>
            );
        }

        if (primaryAmount > 0 && secondaryAmount === 0) {
            return (
                <button
                    key={action.actionType}
                    onClick={() => handlePlayerAction(action.actionType, primaryAmount)}>
                    {`${actionLabel} ${primaryAmount}`}
                </button>
            );
        }

        if (primaryAmount > 0 && secondaryAmount > 0) {
            return (
                <div key={action.actionType} className="action-input-box">
                    <label>{actionLabel}</label>
                    <input
                        type="number"
                        value={betAmount}
                        onChange={(e) => {
                            const value = Math.min(
                                Math.max(parseInt(e.target.value, 10), primaryAmount),
                                secondaryAmount
                            );
                            setBetAmount(value);
                        }}
                        placeholder={`Min: ${primaryAmount}, Max: ${secondaryAmount}`}
                        min={primaryAmount}
                        max={secondaryAmount}
                    />
                    <button onClick={() => handlePlayerAction(action.actionType, betAmount)}>
                        Submit
                    </button>
                </div>
            );
        }
    };

    return (
        <div className="player-action-container">
            <h3>Your Turn</h3>
            {nextPlayerToAct.possibleActionsList.map((action) =>
                renderActionButton(action)
            )}
        </div>
    );
};

export default PlayerActionComponent;
