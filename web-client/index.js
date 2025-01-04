const grpc_pb = require('./generated/texas_holdem_grpc_web_pb.js');
const pb = require('./generated/texas_holdem_pb.js');

const client = new grpc_pb.PokerServicePromiseClient('http://localhost:8080');

/**
 * Sends a JoinGame request to the gRPC server.
 * @param {string} playerName - The name of the player.
 * @param {number} chips - The initial chip count for the player.
 * @returns {Promise<Object>} - A promise resolving to the response object.
 */
const joinGame = (playerName, chips) => {
    return new Promise((resolve, reject) => {
        const joinGameReq = new pb.JoinGameReq();
        joinGameReq.setPlayerName(playerName);
        joinGameReq.setChips(chips);

        client.joinGame(joinGameReq)
            .then((response) => {
                resolve(response.toObject());
            })
            .catch((error) => {
                reject(error.message);
            });
    });
};