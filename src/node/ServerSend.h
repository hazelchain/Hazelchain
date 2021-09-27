//
// Created by chris on 2021-09-02.
//

#ifndef NODETEST_SERVERSEND_H
#define NODETEST_SERVERSEND_H

#include <string>
#include "Server.h"

namespace server::send {
    inline void welcome(SOCKET sockfd, const std::string &message) {
        Packet packet(ServerPacket::welcome);
        packet << message;
        Server::sendData(sockfd, packet);
    }
}

#endif //NODETEST_SERVERSEND_H
