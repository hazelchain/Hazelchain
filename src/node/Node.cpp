//
// Created by chris on 2021-09-13.
//

#include "Node.h"
#include <thread>
#include <algorithm>
#include <unistd.h>
#include "../constants.h"
#include "../storage/logging/Logger.h"
#include "ServerSend.h"

void receive(SOCKET sockfd, ClientPacket packets);

void firstZero(int *arr, int size);

void Node::initialize(int port) {
#ifdef WIN32
    WSAData wsa{};
    struct sockaddr_in serv_addr{};

    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        log(constants::logger, error)
                << "Failed to load server"
                << std::endl;
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

    for (int i = 0; i < MAX_WORKERS; ++i) {
        listenerThreads[i] = std::thread(&Node::_handleConnections, this, i);
        listenerThreads[i].detach();
    }

    start_listening(serverSock_);

#ifdef WIN32
    WSACleanup();
//    delete &wsa;
#endif
}

void Node::start_listening(SOCKET socket) {
    while (!close_) {
        SOCKET newsockfd;
        struct sockaddr_in cli_addr{};
        int clilen = sizeof(cli_addr);

        listen(socket, 5);
        log(constants::logger, info) << "Waiting for incoming connection" << std::endl;
        if ((newsockfd = accept(socket, (struct sockaddr *) &cli_addr, &clilen)) < 0) {
            log(constants::logger, error)
                    << "Failed to connect to incoming connection"
                    << std::endl;
        }
        std::cout << "connected" << std::endl;

        _addToListener(newsockfd);
    }
}

void Node::_addToListener(SOCKET socket) {
    auto[x, y] = util::firstZeroFromMostZeros(incoming_);
    mtx.lock();
    incoming_[x][y] = socket;
    mtx.unlock();
}

void Node::_handleConnections(int index) {
    while (true) {
        FD_SET readfds;
        FD_ZERO(&readfds);
        FD_SET(serverSock_, &readfds);

        mtx.lock();
        if (util::isEmpty(incoming_[index])) {
            mtx.unlock();
            continue;
        }

        for (int i = 0; i < MAX_PER_WORKER; ++i) {
            SOCKET s = incoming_[index][i];
            if (s > 0) {
                FD_SET(s, &readfds);
            }
        }

        int valRead = select(
                0,
                &readfds,
                nullptr,
                nullptr,
                nullptr
        );

        if (valRead < 0) {
            log(constants::logger, error)
                    << "select call failed with error"
                    << std::endl;
            return;
        }

        for (int i = 0; i < MAX_PER_WORKER; ++i) {

            SOCKET s = incoming_[index][i];
            if (FD_ISSET(s, &readfds)) {
                std::vector<char> buffer(256);

                int read = recv(s, &buffer[0], buffer.size(), 0);
                if (read == SOCKET_ERROR) {
                    log(constants::logger, error)
                            << "host disconnected unexpectedly"
                            << std::endl;
                    closesocket(s);
                    incoming_[index][i] = 0;
                }
                if (read == 0) {
                    printf("Host disconnected");

                    closesocket(s);

                    incoming_[index][i] = 0;
                } else {
                    log(constants::logger, info)
                            << "<< "
                            << std::string{buffer.begin(), buffer.end()}
                            << std::endl;
                    send(s, &buffer[0], buffer.size(), 0);
                }
            }
        }
        mtx.unlock();
    }
}
