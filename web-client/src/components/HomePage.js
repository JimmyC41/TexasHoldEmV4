import React, { useContext } from 'react';
import { useNavigate } from 'react-router-dom';
import { GameContext } from '../GameContext';
import useRedirectUser from '../hooks/UseRedirectUser';
import JoinGameComponent from './JoinGameComponent';

const HomePage = () => {
    const { dispatch } = useContext(GameContext);
  	const navigate = useNavigate();
    
	// Redirects re-joining players to the game page
    useRedirectUser();

  	return (
    	<div>
      		<JoinGameComponent dispatch={dispatch} navigate={navigate} />
    	</div>
  	);
};

export default HomePage;
