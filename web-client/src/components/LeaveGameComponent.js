import React, {useContext} from 'react';
import { leaveGame } from '../grpc/UnaryCalls';
import { useNavigate } from 'react-router-dom';
import { loadSessionTokenFromLocalStorage } from '../utils/LocalStorage';
import { GameContext } from '../GameContext';

const LeaveGameComponent = () => {
    const { clearGameStateAndSession } = useContext(GameContext);
    const sessionToken = loadSessionTokenFromLocalStorage();
    const navigate = useNavigate();

    const handleLeaveGame = async () => {
        try {
            const response = await leaveGame(sessionToken);
            console.log('Server Response: ', response.serverMessage);
            clearGameStateAndSession();
            navigate('/');
        } catch {
            console.error('Leave request rejected. Try again.');
        }
    };

    return (
        <div>
            <button onClick={handleLeaveGame}>Leave Game</button>
        </div>
    );
}

export default LeaveGameComponent;