//
// Created by chris on 2021-08-13.
//

#ifndef HAZELCHAIN_SERVER_H
#define HAZELCHAIN_SERVER_H

#define CONNECT_MAX 8

#include "../storage/logging/Logger.h"
#include "../storage/Lookup.h"

#pragma comment(lib, "ws2_32.lib") // for visual studio

namespace {
    enum operation {
        x00,
        x01,
        x02,
        null
        };

    Lookup<std::string, operation> opcodes{
        {"0x00", operation::x00},
        {"0x01", operation::x01},
        {"0x02", operation::x02},
        };
}

namespace node {
    class Server {
    private:
        int port_;
        std::string name_;

        WSAData wsa;
        SOCKET self, clients[CONNECT_MAX] = {};

        void _respond(SOCKET s, sockaddr_in, operation op, std::vector<std::string> args);

    public:
        explicit Server(std::string name, int port);

        int run();


    };
}

#endif //HAZELCHAIN_SERVER_H
