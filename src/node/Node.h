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
#include "../constants.h"
#include "../storage/logging/Logger.h"
#include "../util/sockutil.h"

#define PROTOCOL_VERSION 1
#define MAX_OUTGOING 8
#define MAX_INCOMING 125
#define MAX_WORKERS 5
#define MAX_PER_WORKER MAX_INCOMING / MAX_WORKERS
#define PORT 10541

using json = nlohmann::json;

namespace dns {
    inline std::vector<std::string> getFromDns(const std::string &domain) {
#ifdef WIN32
        util::initWSA();
#endif
        hostent *h = gethostbyname(domain.c_str());
        if (h == nullptr)
            log(constants::logger, error)
                    << "error: "
                    << WSAGetLastError()
                    << std::endl;

        std::vector<std::string> out;
        auto **addr_list = (struct in_addr **) h->h_addr_list;
        for (int i = 0; addr_list[i]; ++i) {
            out.emplace_back(inet_ntoa(*addr_list[i]));
        }
#ifdef WIN32
        WSACleanup();
#endif
        return out;
    }
}

class Node {
private:
    struct TCP {
        std::mutex mtx;
        SOCKET sock_ = -1;
        std::thread threads_[MAX_WORKERS];
        std::array<std::array<SOCKET, MAX_PER_WORKER>, MAX_WORKERS> children_ = {{0}};
    };

    struct UDP {
        SOCKET sock_ = -1;
    };

    TCP tcp = TCP();
    UDP udp = UDP();
    bool stop_ = false;

    void _handleTcpConnections(int index);

    void _addToTcpListenerThread(SOCKET socket);

    void _startListening(SOCKET socket);

    void _initializeTcp();

    void _initializeUdp();

protected:
    static Node *instance_;

    Node() = default;

public:
    Node(Node &other) = delete;

    void operator=(const Node &) = delete;

    static Node &instance();

    void initialize();

    void stop() { stop_ = true; }

};

#endif //HAZELCHAIN_NODE_H
