cmake_minimum_required(VERSION 3.16)
project(TexasHoldEm VERSION 1.0 LANGUAGES CXX)

# Project Setup
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
include(${CMAKE_SOURCE_DIR}/build/Debug/generators/conan_toolchain.cmake)

# Common Directories
set(SERVER_DIR ${PROJECT_SOURCE_DIR}/server)
set(INCLUDE_DIR ${SERVER_DIR}/include)
set(PROTO_DIR ${PROJECT_SOURCE_DIR}/proto)
set(GEN_DIR ${SERVER_DIR}/generated)

# Dependencies
find_package(Boost REQUIRED COMPONENTS random)
find_package(GTest REQUIRED)
find_package(Protobuf REQUIRED)
find_package(gRPC REQUIRED)
find_package(Threads REQUIRED)

# Use Conan version of Protobuf, ignore Homebrew
set(Protobuf_PROTOC_EXECUTABLE "/Users/jimmy/.conan2/p/b/proto6f9b50924eae0/p/bin/protoc")
list(REMOVE_ITEM CMAKE_PREFIX_PATH "/opt/homebrew")

# Protobuf Generation
file(MAKE_DIRECTORY ${GEN_DIR})
set(PROTO_FILE ${PROTO_DIR}/texas_holdem.proto)
set(PROTO_SRC ${GEN_DIR}/texas_holdem.pb.cc)
set(PROTO_HDR ${GEN_DIR}/texas_holdem.pb.h)
set(GRPC_SRC ${GEN_DIR}/texas_holdem.grpc.pb.cc)
set(GRPC_HDR ${GEN_DIR}/texas_holdem.grpc.pb.h)

get_target_property(GRPC_CPP_PLUGIN_LOCATION gRPC::grpc_cpp_plugin IMPORTED_LOCATION)

add_custom_command(
    OUTPUT ${PROTO_SRC} ${PROTO_HDR} ${GRPC_SRC} ${GRPC_HDR}
    COMMAND ${Protobuf_PROTOC_EXECUTABLE}
    ARGS --grpc_out=${GEN_DIR}
         --cpp_out=${GEN_DIR}
         -I ${PROTO_DIR}
         --plugin=protoc-gen-grpc=${GRPC_CPP_PLUGIN_LOCATION}
         ${PROTO_FILE}
)

add_library(proto STATIC ${PROTO_SRC} ${GRPC_SRC})
target_include_directories(proto PUBLIC ${GEN_DIR})
target_link_libraries(proto PUBLIC protobuf::libprotobuf gRPC::grpc++)

# Library Setup
file(GLOB SRC_FILES
    server/src/**/*.cpp
    server/src/*.cpp)

add_library(HoldEmLibrary STATIC ${SRC_FILES})
target_include_directories(HoldEmLibrary
    PRIVATE
        ${INCLUDE_DIR}
        ${GEN_DIR}
)
target_link_libraries(HoldEmLibrary PRIVATE proto Boost::random)

# Testing
enable_testing()
include_directories(${GTEST_INCLUDE_DIRS})

function(addTest TEST_NAME TEST_FILE)
    add_executable(${TEST_NAME} ${TEST_FILE})
    target_link_libraries(${TEST_NAME} PRIVATE HoldEmLibrary GTest::GTest GTest::Main Threads::Threads)
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endfunction()

set(TEST_FILES
    PlayerTest
    PositionTest
    DealerTest
    HandRankTest
    ActionTest
    PotManagerTest
)

foreach(TEST_NAME IN LISTS TEST_FILES)
    addTest(${TEST_NAME} server/test/Services/${TEST_NAME}.cpp)
endforeach()

# Main executable
add_executable(PokerMain server/main.cpp)
target_include_directories(PokerMain PRIVATE ${INCLUDE_DIR} ${GEN_DIR})
target_link_libraries(PokerMain PRIVATE HoldEmLibrary proto)

add_custom_target(run
    COMMAND PokerMain
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)
