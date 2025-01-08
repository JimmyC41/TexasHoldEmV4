import React, { useContext } from 'react';
import { GameContext } from '../GameContext';
import { useNavigate } from 'react-router-dom';

const ManualResetGameComponent = () => {
    const navigate = useNavigate();
    const { clearGameStateAndSession } = useContext(GameContext);

    const handleManualReset = () => {
        clearGameStateAndSession();
        navigate('/');
    };

    return (
        <div>
            <button onClick={handleManualReset}>Reset Game</button>
        </div>
    );
};

export default ManualResetGameComponent;