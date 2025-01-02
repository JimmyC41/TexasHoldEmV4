const grpc = require('@grpc/grpc-js');
const texasHoldemProto = require('./protoc/texas_holdem_grpc_pb');
const texasHoldemMessages = require('./protoc/texas_holdem_pb');

// Create a gRPC client
const client = new texasHoldemProto.PokerServiceClient("0.0.0.0:50051", grpc.credentials.createInsecure());

// Join Game RPC
function joinGame(playerName, chips) {
    // Create the request message
    const request = new texasHoldemMessages.JoinGameReq();
    request.setPlayerName(playerName);
    request.setChips(chips);

    // Make the gRPC call
    client.joinGame(request, (error, response) => {
        if (error) {
            console.error('Error:', error.message);
        } else {
            console.log('Response:', response.getMessage());
        }
    });
}

// Read input from the user
const readline = require('readline').createInterface({
    input: process.stdin,
    output: process.stdout,
});

readline.question('Enter player name: ', (playerName) => {
    readline.question('Enter chips: ', (chips) => {
        joinGame(playerName, parseInt(chips, 10));
        readline.close();
    });
});
