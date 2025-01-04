const grpcProto = require('./generated/texas_holdem_grpc_web_pb.js');
const proto = require('./generated/texas_holdem_pb.js');

console.log('grpcProto:', grpcProto);
console.log('proto:', proto);

const client = new grpcProto.PokerServicePromiseClient('http://localhost:8080');
const joinGameReq = new proto.JoinGameReq();

joinGameReq.setPlayerName('Jimmy');
joinGameReq.setChips(1000);

client.joinGame(joinGameReq)
    .then((response) => {
        console.log('Join Game Response', response.toObject())
    })
    .catch((error) => {
        console.log('Error:', error.message);
    });