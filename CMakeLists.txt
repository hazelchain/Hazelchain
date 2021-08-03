cmake_minimum_required(VERSION 3.16.3)
project(Hazelchain CXX)

set(CMAKE_CXX_STANDARD 17)
set(FETCH_ITEMS FALSE)

message(ERROR ${CMAKE_BINARY_DIR})

include(FetchContent)
include(Fetch.cmake)

fetch_repo(curl "https://github.com/curl/curl.git" "master")
fetch_url(curlpp "https://github.com/jpbarrette/curlpp/archive/refs/tags/v0.8.1.tar.gz")
fetch_repo(boost "https://github.com/boostorg/boost.git" "master")

set(CURL_INCLUDE_DIR ${curl_SOURCE_DIR})
set(CURL_LIBRARY ${curl_BINRAY_DIR})

add_executable(Hazelchain
        src/main.cpp
        src/Block.cpp src/Block.h
        src/util/util.h
        src/util/strutil.h
        src/storage/tree/TransactionTree.cpp src/storage/tree/TransactionTree.h
        src/Transaction.cpp src/Transaction.h
        src/storage/tree/TransactionNode.cpp src/storage/tree/TransactionNode.h
        src/storage/logging/Logger.cpp src/storage/logging/Logger.h
        )

message(STATUS "including directories")
add_subdirectory(${curlpp_SOURCE_DIR} ${curlpp_BINARY_DIR})
include_directories(
        ${boost_SOURCE_DIR}
        libs/json
        libs/sha256
        libs/sqlite
)
message(STATUS "included directories")

message(STATUS "Complete!")
