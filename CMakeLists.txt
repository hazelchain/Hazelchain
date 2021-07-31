cmake_minimum_required(VERSION 3.16.3)
project(Hazelchain)

set(CMAKE_CXX_STANDARD 17)

add_executable(Hazelchain
        src/main.cpp
        src/Block.cpp src/Block.h
        src/util/util.h
        src/util/strutil.h
        src/storage/tree/TransactionTree.cpp src/storage/tree/TransactionTree.h
        src/Transaction.cpp src/Transaction.h
        src/storage/tree/TransactionNode.cpp src/storage/tree/TransactionNode.h
        src/storage/logging/Logger.cpp src/storage/logging/Logger.h
#        src/node/client.h src/node/server.h # Christian is working on these files locally
        )

include_directories(libs/boost)
include_directories(libs/httpRequests)
include_directories(libs/json)
include_directories(libs/sha256)
include_directories(libs/sqlite)
