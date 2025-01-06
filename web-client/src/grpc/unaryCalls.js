const grpc_pb = require('../../generated/texas_holdem_grpc_web_pb.js');
const pb = require('../../generated/texas_holdem_pb.js');
const client = new grpc_pb.PokerServicePromiseClient('http://localhost:8080');

/**
 * gRPC method to add a new player to the game.
 * @param {string} playerName
 * @param {number} chips
 * @returns {Promise<Object>}
 */
export const joinGame = (playerName, chips) => {
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
export const leaveGame = (playerName) => {
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
export const playerAction = (id, type, amount) => {
    const playerActionReq = new pb.PlayerActionReq();
    playerActionReq.setPlayerId(id);
    playerActionReq.setActionType(type);
    playerActionReq.setActionAmount(amount);
    return grpcRequest(client.playerAction.bind(client), playerActionReq);
}

/**
 * Helper function to send a gRPC request and handle the promise.
 * @param {Function} method - The gRPC client method to call.
 * @param {Object} request - The request object for the gRPC call.
 * @returns {Promise<Object>} - A promise resolving to the response object.
 */
export const grpcRequest = (method, request) => {
    return new Promise((resolve, reject) => {
        method(request)
            .then((response) => resolve(response.toObject()))
            .catch((error) => reject(error.message));
    });
};