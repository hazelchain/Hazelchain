cmake_minimum_required(VERSION 3.16.3)
project(Flamecoin)

set(CMAKE_CXX_STANDARD 17)
set(Boost_INCLUDE_DIR ../libraries/boost_1_76_0)

add_executable(Flamecoin
        main.cpp
        libs/sha256/sha256.cpp libs/sha256/sha256.h
        Block.cpp Block.h
        storage/tree/Tree.h
        storage/tree/Node.h
        util.h
        storage/tree/TransactionTree.cpp storage/tree/TransactionTree.h
        Transaction.cpp Transaction.h
        storage/tree/TransactionNode.cpp storage/tree/TransactionNode.h
        )

# see https://cmake.org/cmake/help/latest/module/FindBoost.html
find_package(Boost REQUIRED)

include_directories(${Boost_INCLUDE_DIR})
