const grpc_pb = require('../../generated/texas_holdem_grpc_web_pb.js');
const pb = require('../../generated/texas_holdem_pb.js');
const client = new grpc_pb.PokerServicePromiseClient('http://localhost:8080');

import {
    playersUpdateEvent,
    newStreetEvent,
    dealPlayersEvent,
    dealBoardEvent,
    nextPlayerToActEvent,
    newPlayerActionEvent,
    potUpdateEvent,
    showdownEvent,
    potWinnerEvent
} from './gameEvents'

/**
 * gRPC method to listen to events from the server and
 * dispatch actions to Redux for game state updates
 * @param {string} id 
 * @returns 
 */
export const gameStream = (id, dispatch) => {
    const gameStreamReq = new pb.GameStreamReq();
    gameStreamReq.setPlayerId(id);
    const stream = client.gameStream(gameStreamReq);

    // Key: gRPC stream payload property
    // Value: Redux action creator
    const eventMap = {
        playersUpdate: playersUpdateEvent,
        newStreet: newStreetEvent,
        dealPlayers: dealPlayersEvent,
        dealBoard: dealBoardEvent,
        nextPlayerToAct: nextPlayerToActEvent,
        newPlayerAction: newPlayerActionEvent,
        potUpdate: potUpdateEvent,
        showdownEvent: showdownEvent,
        potWinnerEvent: potWinnerEvent
    };

    stream.on('data', (response) => {
        const event = response.toObject();
        console.log('Raw Event Data:', event);

        for (let streamType in eventMap) {
            // Identify which property the server is streaming
            if (event[streamType]) {

                // Then, dispatch the event to the redux store
                dispatch(eventMap[streamType](event[streamType]));
                break;
            }
        }
    });

    stream.on('error', (error) => {
        console.error('Error in the game stream', error);
    });

    return stream;
}