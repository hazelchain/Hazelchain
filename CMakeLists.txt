#cmake_minimum_required(VERSION 3.16.3)
cmake_minimum_required(VERSION 3.0)
project(Hazelchain CXX)

set(CMAKE_CXX_STANDARD 17)
set(FETCH_ITEMS FALSE)

include(FetchContent)
include(Fetch.cmake)

#fetch_repo(curl "https://github.com/curl/curl.git" "master")
fetch_repo(curlpp_repo "https://github.com/jpbarrette/curlpp.git" "master")
fetch_repo(boost "https://github.com/boostorg/boost.git" "master")

add_executable(${PROJECT_NAME}
        src/main.cpp
        src/Block.cpp src/Block.h
        src/util/util.h
        src/util/strutil.h
        src/storage/tree/TransactionTree.cpp src/storage/tree/TransactionTree.h
        src/Transaction.cpp src/Transaction.h
        src/storage/tree/TransactionNode.cpp src/storage/tree/TransactionNode.h
        src/storage/logging/Logger.cpp src/storage/logging/Logger.h
        src/Http.cpp src/Http.h)

message(STATUS "including directories")
#add_subdirectory(${curlpp_SOURCE_DIR} ${curlpp_BINARY_DIR})
#add_subdirectory(${curlpp_SOURCE_DIR})
#target_link_directories(${PROJECT_NAME} PUBLIC ${curlpp_SOURCE_DIR})
include_directories(
        ${boost_SOURCE_DIR}
        ${curlpp_SOURCE_DIR}
        libs/json
        libs/sha256
        libs/sqlite
)
message(STATUS "included directories")

message(STATUS "Complete!")
