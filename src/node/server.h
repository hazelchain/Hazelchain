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
        xff,
        null
    };

    Lookup<std::string, operation> sendcodes{
            {"0x00", operation::x00}, // error
            {"0x01", operation::x01}, // server welcome, expects client data back with same code
            {"0x02", operation::x02}, //
            {"0xff", operation::xff},
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
