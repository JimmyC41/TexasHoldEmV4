// GENERATED CODE -- DO NOT EDIT!

'use strict';
var grpc = require('@grpc/grpc-js');
var texas_holdem_pb = require('./texas_holdem_pb.js');

function serialize_GameStreamReq(arg) {
  if (!(arg instanceof texas_holdem_pb.GameStreamReq)) {
    throw new Error('Expected argument of type GameStreamReq');
  }
  return Buffer.from(arg.serializeBinary());
}

function deserialize_GameStreamReq(buffer_arg) {
  return texas_holdem_pb.GameStreamReq.deserializeBinary(new Uint8Array(buffer_arg));
}

function serialize_GameStreamRes(arg) {
  if (!(arg instanceof texas_holdem_pb.GameStreamRes)) {
    throw new Error('Expected argument of type GameStreamRes');
  }
  return Buffer.from(arg.serializeBinary());
}

function deserialize_GameStreamRes(buffer_arg) {
  return texas_holdem_pb.GameStreamRes.deserializeBinary(new Uint8Array(buffer_arg));
}

function serialize_JoinGameReq(arg) {
  if (!(arg instanceof texas_holdem_pb.JoinGameReq)) {
    throw new Error('Expected argument of type JoinGameReq');
  }
  return Buffer.from(arg.serializeBinary());
}

function deserialize_JoinGameReq(buffer_arg) {
  return texas_holdem_pb.JoinGameReq.deserializeBinary(new Uint8Array(buffer_arg));
}

function serialize_LeaveGameReq(arg) {
  if (!(arg instanceof texas_holdem_pb.LeaveGameReq)) {
    throw new Error('Expected argument of type LeaveGameReq');
  }
  return Buffer.from(arg.serializeBinary());
}

function deserialize_LeaveGameReq(buffer_arg) {
  return texas_holdem_pb.LeaveGameReq.deserializeBinary(new Uint8Array(buffer_arg));
}

function serialize_PlayerActionReq(arg) {
  if (!(arg instanceof texas_holdem_pb.PlayerActionReq)) {
    throw new Error('Expected argument of type PlayerActionReq');
  }
  return Buffer.from(arg.serializeBinary());
}

function deserialize_PlayerActionReq(buffer_arg) {
  return texas_holdem_pb.PlayerActionReq.deserializeBinary(new Uint8Array(buffer_arg));
}

function serialize_PlayerReqRes(arg) {
  if (!(arg instanceof texas_holdem_pb.PlayerReqRes)) {
    throw new Error('Expected argument of type PlayerReqRes');
  }
  return Buffer.from(arg.serializeBinary());
}

function deserialize_PlayerReqRes(buffer_arg) {
  return texas_holdem_pb.PlayerReqRes.deserializeBinary(new Uint8Array(buffer_arg));
}


var PokerServiceService = exports.PokerServiceService = {
  // Server-to-client game state updates
gameStream: {
    path: '/PokerService/GameStream',
    requestStream: false,
    responseStream: true,
    requestType: texas_holdem_pb.GameStreamReq,
    responseType: texas_holdem_pb.GameStreamRes,
    requestSerialize: serialize_GameStreamReq,
    requestDeserialize: deserialize_GameStreamReq,
    responseSerialize: serialize_GameStreamRes,
    responseDeserialize: deserialize_GameStreamRes,
  },
  // Client-to-server unary calls
joinGame: {
    path: '/PokerService/JoinGame',
    requestStream: false,
    responseStream: false,
    requestType: texas_holdem_pb.JoinGameReq,
    responseType: texas_holdem_pb.PlayerReqRes,
    requestSerialize: serialize_JoinGameReq,
    requestDeserialize: deserialize_JoinGameReq,
    responseSerialize: serialize_PlayerReqRes,
    responseDeserialize: deserialize_PlayerReqRes,
  },
  leaveGame: {
    path: '/PokerService/LeaveGame',
    requestStream: false,
    responseStream: false,
    requestType: texas_holdem_pb.LeaveGameReq,
    responseType: texas_holdem_pb.PlayerReqRes,
    requestSerialize: serialize_LeaveGameReq,
    requestDeserialize: deserialize_LeaveGameReq,
    responseSerialize: serialize_PlayerReqRes,
    responseDeserialize: deserialize_PlayerReqRes,
  },
  playerAction: {
    path: '/PokerService/PlayerAction',
    requestStream: false,
    responseStream: false,
    requestType: texas_holdem_pb.PlayerActionReq,
    responseType: texas_holdem_pb.PlayerReqRes,
    requestSerialize: serialize_PlayerActionReq,
    requestDeserialize: deserialize_PlayerActionReq,
    responseSerialize: serialize_PlayerReqRes,
    responseDeserialize: deserialize_PlayerReqRes,
  },
};

exports.PokerServiceClient = grpc.makeGenericClientConstructor(PokerServiceService);
