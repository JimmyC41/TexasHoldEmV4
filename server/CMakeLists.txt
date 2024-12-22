cmake_minimum_required(VERSION 3.10)

project(TexasHoldEmServer VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB SRC_FILES
    src/*.cpp
    src/States/*.cpp
)

add_library(HoldEmLibrary ${SRC_FILES})

add_executable(PokerMain main.cpp)

target_link_libraries(PokerMain PRIVATE HoldEmLibrary)

add_custom_target(run
    COMMAND PokerMain
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)