cmake_minimum_required(VERSION 3.16)
project(TexasHoldEmServer VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Boost REQUIRED COMPONENTS random)
find_package(GTest REQUIRED)

include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB SRC_FILES
    server/src/Entities/*.cpp
    server/src/Shared/*.cpp
    server/src/Services/*.cpp
    server/src/States/*.cpp
    server/src/Utils/*.cpp
    server/src/*.cpp
)

add_library(HoldEmLibrary ${SRC_FILES})

target_link_libraries(HoldEmLibrary PRIVATE Boost::random)

enable_testing()

include_directories(${GTEST_INCLUDE_DIRS})

function(addTest TEST_NAME TEST_FILE)
    add_executable(${TEST_NAME} ${TEST_FILE})
    target_link_libraries(${TEST_NAME} PRIVATE HoldEmLibrary GTest::GTest GTest::Main pthread)
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endfunction()

set(TEST_FILES
    PlayerTest
    PositionTest
    DealerTest
    HandRankTest
    ActionTest
    PotManagerTest
    IOTest
)

foreach(TEST_NAME IN LISTS TEST_FILES)
    addTest(${TEST_NAME} server/test/Services/${TEST_NAME}.cpp)
endforeach()

add_executable(PokerMain server/main.cpp)
target_link_libraries(PokerMain PRIVATE HoldEmLibrary)

add_custom_target(run
    COMMAND PokerMain
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)

add_custom_target(run_tests
    COMMAND ctest --output-on-failure
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Running Tests"
)
