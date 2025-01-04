import { PokerServicePromiseClient } from "C:\Users\Jimmy\Projects\TexasHoldEmV4\web-client\generated\texas_holdem_grpc_web_pb.js"
import { JoinGameReq } from "C:\Users\Jimmy\Projects\TexasHoldEmV4\web-client\generated\texas_holdem_pb.js"

// Instantiate the client
const client = new PokerServicePromiseClient('http://localhost:8080');

const joinGameReq = new JoinGameReq();
joinGameReq.setPlayername('Jimmy');
joinGameReq.setChips(1000);

client.joinGame(joinGameReq)
    .then((response) => {
        console.log('Join Game Response', response.toObject())
    })
    .catch((error) => {
        console.log('Error:', error.message);
    });