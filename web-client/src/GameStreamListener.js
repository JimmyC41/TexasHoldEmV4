import React, { useContext, useEffect } from 'react';
import { GameContext } from './GameContext';
import { gameStream } from './grpc/StreamingCalls';

const GameStreamListener = ({playerId}) => {
    const { dispatch } = useContext(GameContext);

    useEffect(() => {
        const stream = gameStream(playerId, dispatch);

        return () => {
            stream.cancel();
        };
    }, [playerId, dispatch]);

    return null;
};

export default GameStreamListener;