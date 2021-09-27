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
#include "Packet.h"

#define MAX_NOT_TEMP 3
#define PROTOCOL_VERSION 1

using json = nlohmann::json;

typedef struct {
    SOCKET servSock;
    SOCKET recvSock;
} node_t;

class Node {
private:
    bool close_ = false;
    SOCKET serverSock_ = -1;
    std::vector<node_t> nodes_;

    virtual void _handleConnection(SOCKET sockfd);

public:
    void initialize(int port);

    void start_listening(SOCKET socket);

//    json receive(SOCKET sockfd) const;
    json receive(SOCKET sockfd,
                 const std::function<json(Packet::values_t)> &func,
                 bool includeHeader = true) const;

    static void sendMessage(SOCKET sockfd, const std::string &prompt);

    static void sendData(SOCKET sockfd, Packet packet);

};

#endif //HAZELCHAIN_NODE_H
