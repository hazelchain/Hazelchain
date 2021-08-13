cmake_minimum_required(VERSION 3.16.3)
project(Hazelchain)

set(CMAKE_CXX_STANDARD 17)

if (WIN32)
    set(CMAKE_TOOLCHAIN_FILE "C:/dev/vcpkg/scripts/buildsystems/vcpkg.cmake")
else ()
    set(CMAKE_TOOLCHAIN_FILE "/mnt/c/dev/vcpkg/scripts/buildsystems/vcpkg.cmake")
endif ()

find_package(unofficial-sqlite3 REQUIRED)
find_package(OpenSSL REQUIRED)

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
        src/util/Math.h src/util/Math.cpp src/util/sha256.h)

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