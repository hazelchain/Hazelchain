cmake_minimum_required(VERSION 3.16.3)
project(Hazelchain)

set(CMAKE_CXX_STANDARD 17)
set(Boost_INCLUDE_DIR src/libs/boost)

add_executable(Hazelchain
        src/main.cpp
        src/libs/sha256/sha256.cpp src/libs/sha256/sha256.h
        src/Block.cpp src/Block.h
        src/util/util.h
        src/util/strutil.h
        src/storage/tree/TransactionTree.cpp src/storage/tree/TransactionTree.h
        src/Transaction.cpp src/Transaction.h
        src/storage/tree/TransactionNode.cpp src/storage/tree/TransactionNode.h
        src/storage/logging/Logger.cpp src/storage/logging/Logger.h
#        src/node/client.h src/node/server.h
        )

# see https://cmake.org/cmake/help/latest/module/FindBoost.html
find_package(Boost REQUIRED)

include_directories(${Boost_INCLUDE_DIR})
