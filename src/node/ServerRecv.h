//
// Created by chris on 2021-09-02.
//

#ifndef NODETEST_SERVERRECV_H
#define NODETEST_SERVERRECV_H

#include <map>
#include <string>

namespace server::recv {
    void welcomeReceived(Packet packet, SOCKET sockfd,
                         const std::map<std::string, int> &names) {
        auto &temp = const_cast<std::map<std::string, int> &>(names);
        temp.insert({packet.readString(), sockfd});
    }
}

#endif //NODETEST_SERVERRECV_H
