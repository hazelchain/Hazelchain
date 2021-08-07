cmake_minimum_required(VERSION 3.16.3)
project(Hazelchain)

set(CMAKE_CXX_STANDARD 17)

find_package(boost REQUIRED)
find_package(cpr CONFIG REQUIRED)

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

target_link_libraries(${PROJECT_NAME} PRIVATE cpr boost::boost)

include_directories(
        libs/json
        libs/sha256
        libs/sqlite
)

message(STATUS "Included local dependencies!")

message(STATUS "Complete!")