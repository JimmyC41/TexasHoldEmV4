#!/bin/bash

PROTO_DIR="../proto"
PROTO_FILE="${PROTO_DIR}/texas_holdem.proto"
OUT_DIR="./protoc"

mkdir -p "${OUT_DIR}"

# Generate .js and .grpc.js files
npx grpc_tools_node_protoc \
    --js_out=import_style=commonjs,binary:${OUT_DIR} \
    --grpc_out=grpc_js:${OUT_DIR} \
    --plugin=protoc-gen-grpc=./node_modules/grpc-tools/bin/grpc_node_plugin.exe \
    -I ${PROTO_DIR} \
    ${PROTO_FILE}