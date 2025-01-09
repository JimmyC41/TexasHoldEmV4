import React, { useState, useContext } from 'react';
import { GameContext } from '../GameContext';
import { playerAction } from '../grpc/UnaryCalls';
import { loadSessionTokenFromLocalStorage } from '../utils/LocalStorage'

const PlayerActionComponent = () => {
    const { state } = useContext(GameContext);
    const sessionToken = loadSessionTokenFromLocalStorage();
    const nextPlayerToAct = state?.nextPlayerToAct;

    const [betAmount, setBetAmount] = useState(0);
    const [selectedAction, setSelectedAction] = useState(null);
    const [rangeLimits, setRangeLimits] = useState({ min: 0, max: 0 }); // Store min and max for slider

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

    const getActionLabel = (actionType) => {
        switch (actionType) {
            case 3: return 'Check';
            case 4: return 'Bet';
            case 5: return 'Call';
            case 6: return 'Raise';
            case 7: return 'Fold';
            case 8: return 'Bet All In';
            case 9: return 'Call All In';
            case 10: return 'Raise All In';
            default: return '[?]';
        }
    };

    const renderActionButton = (action) => {
        const actionLabel = getActionLabel(action.actionType);
        const { primaryAmount, secondaryAmount } = action;

        return (
            <button
                key={action.actionType}
                onClick={() => {
                    if (secondaryAmount > 0) {
                        // If the action has a slider, set its range and show the slider
                        setSelectedAction(action.actionType);
                        setRangeLimits({ min: primaryAmount, max: secondaryAmount });
                        setBetAmount(primaryAmount); // Default bet amount to min
                    } else {
                        // If it's a fixed action, perform the action immediately
                        handlePlayerAction(action.actionType, primaryAmount || 0);
                    }
                }}
            >
                {primaryAmount > 0 ? `${actionLabel} ${primaryAmount}` : actionLabel}
            </button>
        );
    };

    return (
        <div className="player-action-container">
            {/* Row for action buttons */}
            <div className="action-buttons">
                {nextPlayerToAct.possibleActionsList.map((action) =>
                    renderActionButton(action)
                )}
            </div>

            {/* Row for slider, dynamically inserted */}
            {selectedAction && (
                <div className="slider-row">
                    <input
                        type="range"
                        min={rangeLimits.min}
                        max={rangeLimits.max}
                        value={betAmount}
                        onChange={(e) => setBetAmount(parseInt(e.target.value, 10))}
                    />
                    <input
                        type="number"
                        min={rangeLimits.min}
                        max={rangeLimits.max}
                        value={betAmount}
                        onChange={(e) => setBetAmount(parseInt(e.target.value, 10))}
                    />
                    <button
                        onClick={() => {
                            handlePlayerAction(selectedAction, betAmount);
                            setSelectedAction(null); // Reset slider after action
                        }}
                    >
                        Submit
                    </button>
                </div>
            )}
        </div>
    );
};

export default PlayerActionComponent;
