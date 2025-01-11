import React, { useState, useEffect, useContext } from 'react';
import { GameContext } from '../GameContext';
import { playerAction } from '../grpc/UnaryCalls';
import { loadSessionTokenFromLocalStorage } from '../utils/LocalStorage';

const PlayerActionComponent = () => {
    const { state } = useContext(GameContext);
    const sessionToken = loadSessionTokenFromLocalStorage();
    const nextPlayerToAct = state?.nextPlayerToAct;

    const [betAmount, setBetAmount] = useState(0);
    const [selectedAction, setSelectedAction] = useState(null);
    const [rangeLimits, setRangeLimits] = useState({ min: 0, max: 0 });
    const [timer, setTimer] = useState(30);

    useEffect(() => {
        if (!nextPlayerToAct || sessionToken !== nextPlayerToAct.playerToAct) return;

        const countdown = setInterval(() => {
            setTimer((prev) => {
                if (prev <= 1) {
                    clearInterval(countdown);
                    handleAutoFold();
                    return 0;
                }
                return prev - 1;
            });
        }, 1000);

        return () => clearInterval(countdown);
    }, [nextPlayerToAct, sessionToken]);

    const handlePlayerAction = async (actionType, amount) => {
        try {
            const response = await playerAction(sessionToken, actionType, amount);
            console.log('Server response: ', response.serverMessage);
        } catch (error) {
            console.error('Action request rejected. Try again.');
        }
    };

    // Fold players if they time out
    const handleAutoFold = () => {
        console.log('Auto-folding player due to timeout.');
        handlePlayerAction(7, 0);
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
                        setSelectedAction(action.actionType);
                        setRangeLimits({ min: primaryAmount, max: secondaryAmount });
                        setBetAmount(primaryAmount);
                    } else {
                        handlePlayerAction(action.actionType, primaryAmount || 0);
                    }
                }}
            >
                {primaryAmount > 0 ? `${actionLabel} ${primaryAmount}` : actionLabel}
            </button>
        );
    };

    if (!nextPlayerToAct || sessionToken !== nextPlayerToAct.playerToAct) {
        return null;
    }

    return (
        <div className="player-action-container">
            <div className="timer">Time remaining: {timer} seconds</div>

            <div className="action-buttons">
                {nextPlayerToAct.possibleActionsList.map((action) =>
                    renderActionButton(action)
                )}
            </div>

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
                            setSelectedAction(null);
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
