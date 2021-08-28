//
// Created by chris on 2021-08-13.
//

#ifndef HAZELCHAIN_SERVER_H
#define HAZELCHAIN_SERVER_H

#define CONNECT_MAX 8

#include "../storage/logging/Logger.h"
#include "../storage/Lookup.h"

#pragma comment(lib, "ws2_32.lib") // for visual studio

namespace node {
    class Server {
    private:
        int port_;
        std::string name_;

        WSAData wsa_;
        SOCKET self_, clients_[CONNECT_MAX] = {};

    public:
        explicit Server(std::string name, int port);

        Server();

        int run();

    };
}

#endif //HAZELCHAIN_SERVER_H
