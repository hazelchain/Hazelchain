//
// Created by chris on 2021-09-13.
//

#include "Node.h"
#include <thread>
#include <algorithm>
#include <unistd.h>
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

void resolveAddress(const char *name, int family, const char *service, sockaddr_storage *pAddr) {
    addrinfo *result_list = nullptr;
    addrinfo hints = {};
    hints.ai_family = family;
    hints.ai_socktype = SOCK_DGRAM;
    if (getaddrinfo(name, service, &hints, &result_list) == 0) {
        memcpy(pAddr, result_list->ai_addr, result_list->ai_addrlen);
        freeaddrinfo(result_list);
    }
}

void Node::initialize() {
    if (initialized_) return;
    initialized_ = true;
#ifdef WIN32
    util::initWSA();
#endif
    std::cout << "a" << std::endl;

    _initializeUdp();
    std::cout << "b" << std::endl;
    _initializeTcp();
    std::cout << "c" << std::endl;

    tcp.listener = std::thread(&Node::_startListeningOnTcp, this);
    std::cout << "d" << std::endl;
    // initialize udp listener here

#ifdef WIN32
    WSACleanup();
#endif
}

void Node::_initializeTcp() {
    log(constants::logger, info)
            << "Starting TCP server on port "
            << PORT
            << std::endl;

    if ((tcp.sock = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        log(constants::logger, error)
                << "Failed to initialize socket"
                << std::endl;
        exit(1);
    }

    memset((char *) &tcp.address, 0, sizeof(tcp.address));
    tcp.address.sin_family = AF_INET;
    tcp.address.sin_port = htons(PORT);
    tcp.address.sin_addr.s_addr = INADDR_ANY;
    if (bind(tcp.sock, (struct sockaddr *) &tcp.address, sizeof(tcp.address)) < 0) {
        log(constants::logger, error)
                << "Failed to bind socket to address"
                << std::endl;;
        exit(1);
    }

    for (int i = 0; i < MAX_WORKERS; ++i) {
        tcp.threads[i] = std::thread(&Node::_handleTcpConnections, this, i);
        tcp.threads[i].detach();
    }
}

void Node::_initializeUdp() {
    log(constants::logger, info)
            << "Starting UDP server on port "
            << PORT
            << std::endl;

    if ((udp.sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        log(constants::logger, error)
                << "failed to create UDP socket"
                << std::endl;
        exit(1);
    }

    memset(&udp.address, 0, sizeof(udp.address));
    udp.address.sin_family = AF_INET;
    udp.address.sin_port = htons(PORT);
    udp.address.sin_addr.s_addr = INADDR_ANY;

    if (bind(udp.sock, (struct sockaddr *) &udp.address, sizeof(udp.address)) < 0) {
        log(constants::logger, error)
                << "UDP bind failed"
                << std::endl;
        exit(1);
    }
}

void Node::_startListeningOnTcp() {
    while (!stop_) {
        SOCKET newsockfd;
        struct sockaddr_in cli_addr{};
        int length = sizeof(cli_addr);

        listen(tcp.sock, 5);
        log(constants::logger, info) << "Waiting for incoming connection" << std::endl;
        if ((newsockfd = accept(tcp.sock, (struct sockaddr *) &cli_addr, &length)) < 0) {
            log(constants::logger, error)
                    << "Failed to connect to incoming connection"
                    << std::endl;
            continue;
        }
        log(constants::logger, info) << "connected" << std::endl;

        _addToTcpListenerThread(newsockfd);
    }
}

void Node::_addToTcpListenerThread(SOCKET socket) {
    auto[x, y] = firstZeroFromMostZeros(tcp.children);
    tcp.mtx.lock();
    tcp.children[x][y] = socket;
    tcp.mtx.unlock();
}

void Node::_handleTcpConnections(int index) {
    while (!stop_) {
        FD_SET readfds;
        FD_ZERO(&readfds);
        FD_SET(tcp.sock, &readfds);

        tcp.mtx.lock();
        if (util::isEmpty(tcp.children[index])) {
            tcp.mtx.unlock();
            continue;
        }

        for (int i = 0; i < MAX_PER_WORKER; ++i) {
            SOCKET s = tcp.children[index][i];
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

            SOCKET s = tcp.children[index][i];
            if (FD_ISSET(s, &readfds)) {
                std::vector<char> buffer(256);

                int read = recv(s, &buffer[0], buffer.size(), 0);
                if (read == SOCKET_ERROR) {
                    log(constants::logger, error)
                            << "host disconnected unexpectedly"
                            << std::endl;
                    closesocket(s);
                    tcp.children[index][i] = 0;
                } else if (read == 0) {
                    printf("Host disconnected");

                    closesocket(s);

                    tcp.children[index][i] = 0;
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

void Node::sendTo(std::tuple<std::string, int> addr, char *data) {
    sockaddr_storage dest;
    resolveAddress(
            std::get<0>(addr).c_str(),
            AF_INET,
            util::to_string(std::get<1>(addr)).c_str(),
            &dest
    );

    sendto(instance_->udp.sock, data, strlen(data), 0, (sockaddr *) &dest, sizeof(dest));
}

std::tuple<std::vector<char>, Node::address> Node::recvFrom(int size) {
    std::vector<char> buffer(size);
    struct sockaddr_in addrOut;
    int addrOut_size = sizeof(addrOut_size);
    recvfrom(
            instance_->udp.sock,
            &buffer[0],
            buffer.size(),
            0,
            (struct sockaddr *) &addrOut,
            &addrOut_size
    );

    for (char v: buffer) {
        log(constants::logger, info) << std::hex << std::setw(2) << std::setfill('0') << v << " ";
    }
    log(constants::logger, info) << std::endl;

    return {buffer, {inet_ntoa(addrOut.sin_addr), addrOut.sin_port}};
}
