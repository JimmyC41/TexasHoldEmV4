// src/pages/HomePage.jsx
import React, { useContext } from 'react';
import { useNavigate } from 'react-router-dom';
import { GameContext } from '../GameContext';
import useRedirectUser from '../hooks/UseRedirectUser';
import JoinGameComponent from '../components/JoinGameComponent';
import '../HomePageUI.css';

const HomePage = () => {
    const { dispatch } = useContext(GameContext);
    const navigate = useNavigate();
    
    // Redirects re-joining players to the game page
    useRedirectUser();

    return (
        <div className="home-container">
            <div className="central-content">
				<h1 className="page-title">Texas Hold'em</h1>
                <JoinGameComponent dispatch={dispatch} navigate={navigate} />
            </div>
        </div>
    );
};

export default HomePage;
