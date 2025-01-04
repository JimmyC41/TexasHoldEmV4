const grpc_pb = require('./generated/texas_holdem_grpc_web_pb.js');
const pb = require('./generated/texas_holdem_pb.js');

const client = new grpc_pb.PokerServicePromiseClient('http://localhost:8080');

/**
 * gRPC method to add a new player to the game.
 * @param {string} playerName
 * @param {number} chips
 * @returns {Promise<Object>}
 */
const joinGame = (playerName, chips) => {
    const joinGameReq = new pb.JoinGameReq();
    joinGameReq.setPlayerName(playerName);
    joinGameReq.setChips(chips);
    return grpcRequest(client.joinGame.bind(client, joinGameReq));
};

/**
 * gRPC method to remove an existing player from the game.
 * @param {string} playerName
 * @returns {Promise<Object>}
 */
const leaveGame = (playerName) => {
    const leaveGameReq = new pb.LeaveGameReq();
    leaveGameReq.setPlayerName(playerName);
    return grpcRequest(client.leaveGame.bind(client), leaveGameReq);
}

/**
 * gRPC method to select a new action for the player to act.
 * @param {string} id 
 * @param {ActionType} type 
 * @param {number} amount 
 * @returns 
 */
const playerAction = (id, type, amount) => {
    const playerActionReq = new pb.PlayerActionReq();
    playerActionReq.setPlayerId(id);
    playerActionReq.setActionType(type);
    playerActionReq.setActionAmount(amount);
    return grpcRequest(client.playerAction.bind(client), playerActionReq);
}

/**
 * gRPC method to start a game stream for a player that has joined
 * @param {string} id 
 * @param {Object} eventHandlers - Object containing functions for different game events
 * @param {Function} onStreamError - Callback to handle stream errors
 * @param {Function} onStreamEnd - Callback to handle stream termination
 * @returns 
 */
const gameStream = (id, eventHandlers, onStreamError, onStreamEnd) => {
    const gameStreamReq = new pb.GameStreamReq();
    gameStreamReq.setPlayerId(id);
    const stream = client.gameStream(gameStreamReq);

    const eventTypeMap = {
        playersUpdate: eventHandlers.playersUpdate,
        newStreet: eventHandlers.newStreet,
        dealPlayers: eventHandlers.dealPlayers,
        dealBoard: eventHandlers.dealBoard,
        nextPlayerToAct: eventHandlers.nextPlayerToAct,
        newPlayerAction: eventHandlers.newPlayerAction,
        potUpdate: eventHandlers.potUpdate,
        showdown: eventHandlers.showdown,
        potWinner: eventHandlers.potWinner,
    };

    stream.on('data', (response) => {
        const event = response.toObject();

        for (const [key, handler] of Object.entries(eventTypeMap)) {
            if (event[key] && handler) {
                handler(event[key]);
                return;
            }
    }
    });

    stream.on('error', (error) => {
        console.error('Stream error:', error.message);
        if (onStreamError) onStreamError(error);
    });

    stream.on('end', () => {
        console.log('Stream ended.');
        if (onStreamEnd) onStreamEnd();
    });

    return stream;
}

/**
 * Helper function to send a gRPC request and handle the promise.
 * @param {Function} method - The gRPC client method to call.
 * @param {Object} request - The request object for the gRPC call.
 * @returns {Promise<Object>} - A promise resolving to the response object.
 */
const grpcRequest = (method, request) => {
    return new Promise((resolve, reject) => {
        method(request)
            .then((response) => resolve(response.toObject()))
            .catch((error) => reject(error.message));
    });
};


// const delay = (ms) => new Promise(resolve => setTimeout(resolve, ms));

// const runGameSequence = async () => {
//     try {
//         const joinP1Response = await joinGame('P1', 10000);
//         console.log('Join Game Response for P1:', joinP1Response);

//         await delay(1000); // Pause for 1 second

//         const joinP2Response = await joinGame('P2', 10000);
//         console.log('Join Game Response for P2:', joinP2Response);

//         await delay(1000); // Pause for 1 second

//         const raiseP1Response = await playerAction('P1', pb.ProtoActionType.RAISE, 500);
//         console.log('Player Action Response for P1 (RAISE):', raiseP1Response);

//         await delay(1000); // Pause for 1 second

//         const callP2Response = await playerAction('P2', pb.ProtoActionType.CALL, 500);
//         console.log('Player Action Response for P2 (CALL):', callP2Response);

//         await delay(1000); // Pause for 1 second

//         const foldP1Response = await playerAction('P1', pb.ProtoActionType.FOLD, 0);
//         console.log('Player Action Response for P1 (FOLD):', foldP1Response);
//     } catch (error) {
//         console.error('Error during game sequence:', error);
//     }
// };

// runGameSequence();
