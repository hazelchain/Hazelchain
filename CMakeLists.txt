cmake_minimum_required(VERSION 3.16.3)
project(Hazelchain CXX)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)

message(STATUS "Downloading external dependencies... (1 of 2)")
FetchContent_Declare(
        cpr
        GIT_REPOSITORY https://github.com/whoshuu/cpr.git
        GIT_TAG c8d33915dbd88ad6c92b258869b03aba06587ff9
)
message(STATUS "Downloading external dependencies... (2 of 2")
FetchContent_Declare(
        boost
        GIT_REPOSITORY https://github.com/boostorg/boost.git
        GIT_TAG master
        PREFIX boost
        GIT_SUBMODULES libs/multiprecision
)
FetchContent_MakeAvailable(cpr boost)

message(STATUS "Downloaded external dependencies!")

add_executable(
        ${PROJECT_NAME}
        src/main.cpp
        src/Block.cpp src/Block.h
        src/util/util.h
        src/util/strutil.h
        src/storage/tree/TransactionTree.cpp src/storage/tree/TransactionTree.h
        src/Transaction.cpp src/Transaction.h
        src/storage/tree/TransactionNode.cpp src/storage/tree/TransactionNode.h
        src/storage/logging/Logger.cpp src/storage/logging/Logger.h
        src/util/Http.h
)

message(STATUS "Including local dependencies...")

target_link_libraries(${PROJECT_NAME} PRIVATE cpr::cpr boost)

include_directories(
        libs/json
        libs/sha256
        libs/sqlite
)

message(STATUS "Included local dependencies!")

message(STATUS "Complete!")