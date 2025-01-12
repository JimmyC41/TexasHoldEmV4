#!/bin/bash
rm -rf ./web-client/generated
mkdir -p ./web-client/generated

protoc --proto_path ./proto texas_holdem.proto \
    --plugin=protoc-gen-js="/opt/homebrew/bin/protoc-gen-js" \
    --js_out=import_style=commonjs:./web-client/generated \
    --plugin=proto-gen-grpc-web="/opt/homebrew/bin/protoc-gen-grpc-web" \
    --grpc-web_out=import_style=commonjs,mode=grpcwebtext:./web-client/generated