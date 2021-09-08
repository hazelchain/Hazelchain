//
// Created by chris on 2021-08-31.
//

#include "Server.h"
#include <ws2tcpip.h>
#include <iostream>
#include <unistd.h>
#include <string>
#include <thread>
#include "ServerSend.h"
#include "ServerRecv.h"

Server::~Server() {
    close_ = true;
    std::cout << "Stopping server" << std::endl;
    for (auto &client: clients_) {
        std::cout << "closing socket with "
                  << client.first
                  << " on port "
                  << client.second
                  << "..."
                  << std::endl;

        close(client.second);

        std::cout << "done" << std::endl;
    }

    closesocket(sockfd_);
}

void Server::initialize(int port) {
    WSAData wsa{};
    struct sockaddr_in serv_addr{};

    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        perror("Failed to load server\n");
        exit(1);
    }

    if ((sockfd_ = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        perror("error: failed to initialize socket.\n");
        exit(1);
    }

    memset((char *) &serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    if (bind(sockfd_, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("error: Failed to bind socket to address.\n");
        exit(1);
    }

    start_listening(sockfd_);
}

void Server::start_listening(SOCKET socket) {
    while (!close_) {
        SOCKET newsockfd = -1;
        struct sockaddr_in cli_addr{};
        int clilen = sizeof(cli_addr);

        listen(socket, 5);
        if ((newsockfd = accept(socket, (struct sockaddr *) &cli_addr, &clilen)) < 0) {
            perror("error: Failed to connect to incoming connection.\n");
        }

        std::thread th(&Server::_handleConnection, this, newsockfd);
        th.detach();
    }
}

void Server::_handleConnection(SOCKET sockfd) {
    std::cout << sockfd << ": connected" << std::endl;
    std::vector<char> buffer(256);

    server::send::welcome(sockfd, "What up homie?");
    receive(sockfd);

    while (recv(sockfd, &buffer[0], buffer.size(), 0) > 0) {
        std::cout << &buffer[0];
        sendMessage(sockfd, strcat(&buffer[0], " - understood"));
        buffer.clear();
    }
    close((int) sockfd);

    for (const auto &i: clients_) {
        if (i.second == (int) sockfd) {
            clients_.erase(i.first);
            break;
        }
    }

    std::cout << sockfd << ": disconnected" << std::endl;
}

void Server::sendMessage(SOCKET sockfd, const std::string &prompt) {
    const char *p = prompt.c_str();
    send(sockfd, p, (int) strlen(p), 0);
}

void Server::sendData(SOCKET sockfd, Packet packet) {
    std::cout << sockfd << " << packet id: "
              << packet.getId()
              << " (Client Packet)"
              << std::endl;
    packet.writeLength();
    packet.print();
    send(sockfd, (char *) packet.toArray(), packet.size(), 0);
}

void Server::receive(SOCKET sockfd, int size) const {
    std::vector<char> buffer(size);

    if (recv(sockfd, &buffer[0], buffer.size(), 0) < 0) {
        puts("recv failed");
    }

    Packet pack(buffer);
    std::cout << sockfd << " >> packet id: "
              << pack.getId()
              << " (Client Packet)"
              << std::endl;
    switch ((ClientPackets) pack.getId()) {
        case welcomeReceived:
            server::recv::welcomeReceived(pack, sockfd, clients_);
            for (auto &i: clients_) {
                std::cout << i.first << std::endl;
            }
            break;
    }
}
