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

template<size_t X, size_t Y>
inline std::tuple<int, int> firstZeroFromMostZeros(
        std::array<std::array<SOCKET, Y>, X> arr) {
    int zeros[X] = {0};
    for (int i = 0; i < X; ++i) {
        for (int j = 0; j < Y; ++j) {
            if (arr[i][j] == 0)
                ++zeros[i];
        }
    }
    int most = 0;
    for (int i = 0; i < X; ++i) {
        if (zeros[i] > zeros[most]) most = i;
    }
    return {most, util::firstZero(arr[most], Y)};
}

void Node::initialize() {
    if (initialized_) return;
#ifdef WIN32
    util::initWSA();
#endif

    _initializeUdp();
    _initializeTcp();

    _startListeningOnTcp(tcp.sock_);

#ifdef WIN32
    WSACleanup();
#endif
}

void Node::_initializeTcp() {
    log(constants::logger, info)
            << "Starting TCP server on port "
            << PORT
            << std::endl;

    struct sockaddr_in serv_addr{};

    if ((tcp.sock_ = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        log(constants::logger, error)
                << "Failed to initialize socket"
                << std::endl;;
        exit(1);
    }

    memset((char *) &serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    if (bind(tcp.sock_, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        log(constants::logger, error)
                << "Failed to bind socket to address"
                << std::endl;;
        exit(1);
    }

    for (int i = 0; i < MAX_WORKERS; ++i) {
        tcp.threads_[i] = std::thread(&Node::_handleTcpConnections, this, i);
        tcp.threads_[i].detach();
    }
}

void Node::_initializeUdp() {
    log(constants::logger, info)
            << "Starting UDP server on port "
            << PORT
            << std::endl;
    std::vector<std::string> ips = util::join(
            {
                    util::ipsOf("seeder.unmined.ca")
            }
    );

    for (auto &ip: ips) {
        std::cout << ip << std::endl;
    }
}

void Node::_startListeningOnTcp(SOCKET socket) {
    while (!stop_) {
        SOCKET newsockfd;
        struct sockaddr_in cli_addr{};
        int length = sizeof(cli_addr);

        listen(socket, 5);
        log(constants::logger, info) << "Waiting for incoming connection" << std::endl;
        if ((newsockfd = accept(socket, (struct sockaddr *) &cli_addr, &length)) < 0) {
            log(constants::logger, error)
                    << "Failed to connect to incoming connection"
                    << std::endl;
            continue;
        }
        std::cout << "connected" << std::endl;

        _addToTcpListenerThread(newsockfd);
    }
}

void Node::_addToTcpListenerThread(SOCKET socket) {
    auto[x, y] = firstZeroFromMostZeros(tcp.children_);
    tcp.mtx.lock();
    tcp.children_[x][y] = socket;
    tcp.mtx.unlock();
}

void Node::_handleTcpConnections(int index) {
    while (true) {
        FD_SET readfds;
        FD_ZERO(&readfds);
        FD_SET(tcp.sock_, &readfds);

        tcp.mtx.lock();
        if (util::isEmpty(tcp.children_[index])) {
            tcp.mtx.unlock();
            continue;
        }

        for (int i = 0; i < MAX_PER_WORKER; ++i) {
            SOCKET s = tcp.children_[index][i];
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

            SOCKET s = tcp.children_[index][i];
            if (FD_ISSET(s, &readfds)) {
                std::vector<char> buffer(256);

                int read = recv(s, &buffer[0], buffer.size(), 0);
                if (read == SOCKET_ERROR) {
                    log(constants::logger, error)
                            << "host disconnected unexpectedly"
                            << std::endl;
                    closesocket(s);
                    tcp.children_[index][i] = 0;
                }
                if (read == 0) {
                    printf("Host disconnected");

                    closesocket(s);

                    tcp.children_[index][i] = 0;
                } else {
                    log(constants::logger, info)
                            << "<< "
                            << std::string{buffer.begin(), buffer.end()}
                            << std::endl;
                    send(s, &buffer[0], buffer.size(), 0);
                }
            }
        }
        tcp.mtx.unlock();
    }
}

Node *Node::instance_ = nullptr;

Node *Node::instance() {
    if (instance_ == nullptr) {
        instance_ = new Node();
        return instance_;
    }
    return instance_;
}

void Node::stop() {
    stop_ = true;
    instance_ = nullptr;
    initialized_ = false;
}

