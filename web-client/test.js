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
 * @returns 
 */
const gameStream = (id) => {
    const gameStreamReq = new pb.GameStreamReq();
    gameStreamReq.setPlayerId(id);
    const stream = client.gameStream(gameStreamReq);

    stream.on('data', (response) => {
        const event = response.toObject();
        console.log('Raw Event Data:', event);
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



const runGameSequence = async () => {
    try {
        const joinP1Response = await joinGame('P1', 10000);
        console.log('Join Game Response for P1:', joinP1Response);

        await gameStream('P1');

        await delay(1000); // Pause for 1 second

        const joinP2Response = await joinGame('P2', 10000);
        console.log('Join Game Response for P2:', joinP2Response);
        

        await delay(1000); // Pause for 1 second

        const raise1 = await playerAction('P1', pb.ProtoActionType.RAISE, 500);
        console.log('Player Action Response for P1 (RAISE):', raise1);

        await delay(1000); // Pause for 1 second

        const call2 = await playerAction('P2', pb.ProtoActionType.CALL, 500);
        console.log('Player Action Response for P2 (CALL):', call2);

        await delay(1000); // Pause for 1 second

        const check3 = await playerAction('P1', pb.ProtoActionType.CHECK, 0);
        console.log('Player Action Response for P1 (CHECK):', check3);

        await delay(1000); // Pause for 1 second

        const check4 = await playerAction('P2', pb.ProtoActionType.CHECK, 0);
        console.log('Player Action Response for P2 (CHECK):', check4);

        await delay(1000); // Pause for 1 second

        const check5 = await playerAction('P1', pb.ProtoActionType.CHECK, 0);
        console.log('Player Action Response for P1 (CHECK):', check5);

        await delay(1000); // Pause for 1 second

        const check6 = await playerAction('P2', pb.ProtoActionType.CHECK, 0);
        console.log('Player Action Response for P2 (CHECK):', check6);

        await delay(1000); // Pause for 1 second

        const check7 = await playerAction('P1', pb.ProtoActionType.CHECK, 0);
        console.log('Player Action Response for P1 (CHECK):', check7);

        await delay(1000); // Pause for 1 second

        const check8 = await playerAction('P2', pb.ProtoActionType.CHECK, 0);
        console.log('Player Action Response for P2 (CHECK):', check8);

    } catch (error) {
        console.error('Error during game sequence:', error);
    }
};

runGameSequence();
