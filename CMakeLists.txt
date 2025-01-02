cmake_minimum_required(VERSION 3.16)
project(TexasHoldEm VERSION 1.0 LANGUAGES CXX)

# Set C++ Standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include Conan toolchain and find packages
include(${CMAKE_SOURCE_DIR}/build/build/generators/conan_toolchain.cmake)

find_package(Boost REQUIRED COMPONENTS random)
find_package(GTest REQUIRED)
find_package(Protobuf REQUIRED)
find_package(gRPC REQUIRED)
find_package(Threads REQUIRED)

# Include src directory and generated headers in the build directory
include_directories(${PROJECT_SOURCE_DIR}/include)

# Proto file
set(PROTO_FILE ${CMAKE_SOURCE_DIR}/proto/texas_holdem.proto)

# Output directory for generated files
set(GRPC_OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/proto)
file(MAKE_DIRECTORY ${GRPC_OUTPUT_DIR})

# Generated source and header files
set(PROTO_SRC ${GRPC_OUTPUT_DIR}/texas_holdem.pb.cc)
set(PROTO_HDR ${GRPC_OUTPUT_DIR}/texas_holdem.pb.h)
set(GRPC_SRC ${GRPC_OUTPUT_DIR}/texas_holdem.grpc.pb.cc)
set(GRPC_HDR ${GRPC_OUTPUT_DIR}/texas_holdem.grpc.pb.h)

# gRPC and protobuf generation command
get_target_property(GRPC_CPP_PLUGIN_LOCATION gRPC::grpc_cpp_plugin IMPORTED_LOCATION)

add_custom_command(
    OUTPUT ${PROTO_SRC} ${PROTO_HDR} ${GRPC_SRC} ${GRPC_HDR}
    COMMAND ${Protobuf_PROTOC_EXECUTABLE}
    ARGS --grpc_out=${GRPC_OUTPUT_DIR}
         --cpp_out=${GRPC_OUTPUT_DIR}
         -I ${CMAKE_CURRENT_SOURCE_DIR}/proto
         --plugin=protoc-gen-grpc=${GRPC_CPP_PLUGIN_LOCATION}
         ${PROTO_FILE}
    COMMENT "Generating gRPC C++ files from texas_holdem.proto"
)

# Include the generated files
include_directories(${GRPC_OUTPUT_DIR})

# Protobuf and gRPC library (proto)
add_library(proto
    ${PROTO_SRC}
    ${PROTO_HDR}
    ${GRPC_SRC}
    ${GRPC_HDR}
)

target_link_libraries(proto
    PUBLIC
        protobuf::libprotobuf
        gRPC::grpc++
)

# Gather C++ backend files
file(GLOB SRC_FILES
    server/src/Entities/*.cpp
    server/src/Shared/*.cpp
    server/src/Services/*.cpp
    server/src/States/*.cpp
    server/src/Utils/*.cpp
    server/src/gRPC/*.cpp
    server/src/*.cpp
)

# Create the project library with C++ source code
add_library(HoldEmLibrary
    ${SRC_FILES}
)

# Link proto library to HoldEmLibrary
target_link_libraries(HoldEmLibrary
    PRIVATE
        proto
        Boost::random)

# Include necessary directories for gRPC and Protobuf
target_include_directories(HoldEmLibrary
    PRIVATE
        ${Protobuf_INCLUDE_DIRS}            # Protobuf headers
        ${GRPC_INCLUDE_DIRS}                # gRPC headers
        ${CMAKE_CURRENT_BINARY_DIR}/proto   # For generated .grpc.pb.h files
)

# Enable testing and include GTest directories
enable_testing()
include_directories(${GTEST_INCLUDE_DIRS})

# Define method to add tests
function(addTest TEST_NAME TEST_FILE)
    add_executable(${TEST_NAME} ${TEST_FILE})
    target_link_libraries(${TEST_NAME}
        PRIVATE
            HoldEmLibrary
            GTest::GTest
            GTest::Main
            Threads::Threads
    )
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endfunction()

# Test files
set(TEST_FILES
    PlayerTest
    PositionTest
    DealerTest
    HandRankTest
    ActionTest
    PotManagerTest
)

# Add each test file
foreach(TEST_NAME IN LISTS TEST_FILES)
    addTest(${TEST_NAME} server/test/Services/${TEST_NAME}.cpp)
endforeach()

# Main executable
add_executable(PokerMain server/main.cpp)

# Include nececessary directories
target_include_directories(PokerMain
    PRIVATE
        ${Protobuf_INCLUDE_DIRS}
        ${GRPC_INCLUDE_DIRS}
        ${CMAKE_CURRENT_BINARY_DIR}/proto)

target_link_libraries(PokerMain
    PRIVATE
        HoldEmLibrary
        protobuf::libprotobuf
        gRPC::grpc++
)

add_custom_target(run
    COMMAND PokerMain
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)
