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

# Protobuf sources
set(PROTO_FILES proto/texas_holdem.proto)

#protobuf_generate_cpp(PROTO_SRC PROTO_HDR ${PROTO_FILES})

# gRPC sources
get_target_property(GRPC_CPP_PLUGIN_LOCATION gRPC::grpc_cpp_plugin IMPORTED_LOCATION)
add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/texas_holdem.grpc.pb.cc
           ${CMAKE_CURRENT_BINARY_DIR}/texas_holdem.grpc.pb.h
    COMMAND ${Protobuf_PROTOC_EXECUTABLE}
    ARGS --grpc_out=${CMAKE_CURRENT_BINARY_DIR}
         --cpp_out=${CMAKE_CURRENT_BINARY_DIR}
         -I ${CMAKE_CURRENT_SOURCE_DIR}/proto
         --plugin=protoc-gen-grpc=${GRPC_CPP_PLUGIN_LOCATION}
         ${CMAKE_CURRENT_SOURCE_DIR}/proto/texas_holdem.proto
    DEPENDS ${PROTO_FILES}
    COMMENT "Generating gRPC C++ files from texas_holdem.proto"
)

# Include the generated files
set(GRPC_SRC ${CMAKE_CURRENT_BINARY_DIR}/texas_holdem.grpc.pb.cc)
set(GRPC_HDR ${CMAKE_CURRENT_BINARY_DIR}/texas_holdem.grpc.pb.h)

# Protobuf and gRPC library (proto)
add_library(proto
    ${PROTO_SRC}
    ${PROTO_HDR}
    ${GRPC_SRC}
    ${GRPC_HDR}
)

# gRPC files must be generated BEFORE proto
add_custom_target(grpc_generated_files
    DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/texas_holdem.grpc.pb.cc
            ${CMAKE_CURRENT_BINARY_DIR}/texas_holdem.grpc.pb.h
)
add_dependencies(proto grpc_generated_files)

# Link proto library to necessary libraries
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

# Create the project library
add_library(HoldEmLibrary
    ${SRC_FILES}
    ${PROTO_SRC}
    ${PROTO_HDR}
    ${GRPC_SRC}
    ${GRPC_HDR}
)

# Include necessary directories for gRPC and Protobuf
target_include_directories(HoldEmLibrary
    PRIVATE
        ${Protobuf_INCLUDE_DIRS}     # Protobuf headers
        ${GRPC_INCLUDE_DIRS}         # gRPC headers
        ${CMAKE_CURRENT_BINARY_DIR}   # For generated .grpc.pb.h files
)

# Link proto library to HoldEmLibrary (but don't include paths here)
target_link_libraries(HoldEmLibrary
    PRIVATE
        Boost::random
        proto  # This links the proto library (which includes protobuf and grpc++)
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
    IOTest
)

# Add each test file
foreach(TEST_NAME IN LISTS TEST_FILES)
    addTest(${TEST_NAME} server/test/Services/${TEST_NAME}.cpp)
endforeach()

# Main executable
add_executable(PokerMain server/main.cpp)
target_link_libraries(PokerMain PRIVATE HoldEmLibrary)

add_custom_target(run
    COMMAND PokerMain
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)
