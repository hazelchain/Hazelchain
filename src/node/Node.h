//
// Created by chris on 2021-09-13.
//

#ifndef HAZELCHAIN_NODE_H
#define HAZELCHAIN_NODE_H

#ifdef WIN32

#include <winsock2.h>
#include <ws2tcpip.h>

#endif

#include <vector>
#include <string>
#include <json.hpp>
#include <thread>
#include <mutex>
#include "Packet.h"

#define PROTOCOL_VERSION 1
#define MAX_OUTGOING 8
#define MAX_INCOMING 125
#define MAX_WORKERS 5
#define MAX_PER_WORKER MAX_INCOMING / MAX_WORKERS

using json = nlohmann::json;

class Node {
private:
    bool close_ = false;
    std::mutex mtx;
    SOCKET serverSock_ = -1;

    std::thread listenerThreads[MAX_WORKERS];

    std::array<std::array<SOCKET, MAX_PER_WORKER>, MAX_WORKERS> incoming_;

    void _handleConnections(int index);

    void _addToListener(SOCKET socket);

public:
    void initialize(int port);

    void start_listening(SOCKET socket);

};

#endif //HAZELCHAIN_NODE_H
