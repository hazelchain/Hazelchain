//
// Created by chris on 2021-09-13.
//

#include "Node.h"
#include <thread>
#include <algorithm>
#include "../constants.h"
#include "../storage/logging/Logger.h"
#include "ServerSend.h"

void receive(SOCKET sockfd, ClientPacket packets);

void Node::initialize(int port) {
#ifdef WIN32
    WSAData wsa{};
    struct sockaddr_in serv_addr{};

    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        log(constants::logger, error)
                << "Failed to load server"
                << std::endl;;
        exit(1);
    }
#endif

    if ((serverSock_ = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        log(constants::logger, error)
                << "Failed to initialize socket"
                << std::endl;;
        exit(1);
    }

    memset((char *) &serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    if (bind(serverSock_, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        log(constants::logger, error)
                << "Failed to bind socket to address"
                << std::endl;;
        exit(1);
    }

    start_listening(serverSock_);

#ifdef WIN32
    WSACleanup();
    delete &wsa;
#endif
}

void Node::start_listening(SOCKET socket) {
    while (!close_) {
        SOCKET newsockfd = -1;
        struct sockaddr_in cli_addr{};
        int clilen = sizeof(cli_addr);

        listen(socket, 5);
        if ((newsockfd = accept(socket, (struct sockaddr *) &cli_addr, &clilen)) < 0) {
            log(constants::logger, error)
                    << "Failed to connect to incoming connection"
                    << std::endl;;
        }

        std::thread t(&Node::_handleConnection, this, newsockfd);
        t.detach();
    }
}

void Node::_handleConnection(SOCKET sockfd) {
    std::vector<char> buffer(256);

    std::function<json(Packet::values_t)> p
            = [](const Packet::values_t &values) {
                return json{};
            };

    json data = receive(sockfd, [](const Packet::values_t &values) {
        return json{};
    }, false);
}

json Node::receive(SOCKET sockfd,
                   const std::function<json(Packet::values_t)> &func,
                   bool includeHeader) const {
    std::vector<char> buffer(256);

    if (recv(sockfd, &buffer[0], buffer.size(), 0) < 0) {
        log(constants::logger, error) << "Receive failed" << std::endl;;
    }

    Packet::values_t vals;
    Packet pack(buffer);
    switch ((ClientPacket) pack.getId()) {
        case HANDSHAKE:
            vals.push_back(pack.readUInt());       //  \
            vals.push_back(pack.readUInt());       //  |
            vals.push_back(pack.readULongLong());  //  |
            vals.push_back(pack.readString());     //  | header
            vals.push_back(pack.readString());     //  |
            vals.push_back(pack.readULongLong());  //  |
            vals.push_back(pack.readULong());      //  /
            break;
    }
}
