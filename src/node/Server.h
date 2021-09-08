//
// Created by chris on 2021-08-31.
//

#ifndef NODETEST_SERVER_H
#define NODETEST_SERVER_H


#include <winsock2.h>
#include <string>
#include <vector>
#include <stack>
#include <map>
#include "Packet.h"

class Server {
private:
    bool close_ = false;
    SOCKET sockfd_ = -1;
    std::map<std::string, int> clients_;

    virtual void _handleConnection(SOCKET sockfd);

public:
    Server() = default;

    ~Server();

    void initialize(int port);

    virtual void start_listening(SOCKET socket);

    void receive(SOCKET sockfd, int size = 256) const;

    static void sendMessage(SOCKET sockfd, const std::string &prompt);

    static void sendData(SOCKET sockfd, Packet packet);
};

void sendWelcome(SOCKET sockfd, const std::string &message);


#endif //NODETEST_SERVER_H
