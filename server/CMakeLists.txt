cmake_minimum_required(VERSION 3.10)

project(TexasHoldEmServer VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB SRC_FILES
    src/Entities/*.cpp
    src/Shared/*.cpp
    src/Services/*.cpp
    src/Utils/*.cpp
    src/*.cpp
)

add_library(HoldEmLibrary ${SRC_FILES})

# TESTS

enable_testing()
find_package(GTest REQUIRED)
include_directories((${GTEST_INCLUDE_DIRS}))

function(addTest TEST_NAME, TEST_FILE)
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
    addTest(${TEST_NAME}  test/Services/${TEST_NAME}.cpp)
endforeach()

# MAIN FUNCTION

add_executable(PokerMain main.cpp)
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