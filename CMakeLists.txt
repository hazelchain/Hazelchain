cmake_minimum_required(VERSION 3.16.3)
project(Hazelchain)

set(CMAKE_CXX_STANDARD 17)

find_package(unofficial-sqlite3 REQUIRED)
find_package(OpenSSL REQUIRED)

add_executable(
        ${PROJECT_NAME}
        src/main.cpp
        src/constants.h
        src/Block.h src/Block.cpp
        src/Transaction.cpp src/Transaction.h
        src/util/util.h
        src/util/strutil.h
        src/util/Http.h
        src/util/Math.h src/util/Math.cpp
        src/util/sha256.h
        src/storage/Lookup.h
        src/storage/logging/Logger.h src/storage/logging/Logger.cpp
        src/storage/tree/TransactionTree.h src/storage/tree/TransactionTree.cpp
        src/storage/tree/TransactionNode.h src/storage/tree/TransactionNode.cpp
        src/node/Server.h src/node/Server.cpp
        src/node/Packet.h src/node/Packet.cpp
)

if (WIN32)
    target_link_libraries(${PROJECT_NAME} wsock32 ws2_32)
endif ()

target_link_libraries(
        ${PROJECT_NAME}
        unofficial::sqlite3::sqlite3
        OpenSSL::SSL OpenSSL::Crypto
)

include_directories(
        libs/json
        libs/sha256
)

message(STATUS "Done!")