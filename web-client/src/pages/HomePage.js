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
                <div className="design-explanations">
                    <h4>
                        <a 
                            href="https://github.com/JimmyC41" 
                            target="_blank" 
                            rel="noopener noreferrer"
                            className="github-link"
                        >
                            https://github.com/JimmyC41
                        </a>
                    </h4>
                    <ul>
                        <li>Description</li>
                        <li>Backend Features</li>
                        <li>Frontend Features</li>
                        <li>Game Rules</li>
                    </ul>
                </div>
            </div>
        </div>
    );
};

export default HomePage;
