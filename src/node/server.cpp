//
// Created by chris on 2021-08-13.
//

#include <utility>
#include <winsock2.h>
#include "server.h"
#include "../constants.h"

node::Server::Server(std::string name, int port)
        : port_(port),
          name_(std::move(name)) {
}

node::Server::Server() : name_("server"), port_(1234) {
}

int node::Server::run() {
    SOCKET new_socket;
    sockaddr_in server{}, address{};
    int MAXRECV = 1024;
    fd_set readfds;
    char *buffer = (char *) malloc((MAXRECV + 1) * sizeof(char));

    log(constants::logger, info)
            << "Loading "
            << name_
            << "..."
            << logger::endl;

    if (WSAStartup(MAKEWORD(2, 2), &wsa_) != 0) {
        log(constants::logger, error)
                << "Failed to load server: "
                << WSAGetLastError()
                << logger::endl;
        return 1;
    }

    if ((self_ = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        log(constants::logger, error)
                << "Could not create server socket: "
                << WSAGetLastError()
                << logger::endl;
        return 1;
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(port_);

    if (bind(self_, (struct sockaddr *) &server, sizeof(server)) == SOCKET_ERROR) {
        log(constants::logger, error)
                << "Server Bind failed: "
                << WSAGetLastError()
                << logger::endl;
        return 1;
    }

    listen(self_, 3);

    log(constants::logger, info)
            << "Server loaded "
            << logger::endl;


    log(constants::logger, info)
            << "Ready to receive incoming connections"
            << logger::endl;

    int addrlen = sizeof(struct sockaddr_in);
    while (true) {
        FD_ZERO(&readfds);
        FD_SET(self_, &readfds);

        for (auto[i, s] = std::tuple{0, SOCKET()}; i < CONNECT_MAX; ++i) {
            s = clients_[i];
            if (s > 0) {
                FD_SET(s, &readfds);
            }
        }

        int activity = select(0,
                              &readfds,
                              nullptr,
                              nullptr,
                              nullptr
        );

        if (activity == SOCKET_ERROR) {
            log(constants::logger, error)
                    << "select call failed with error code: "
                    << WSAGetLastError()
                    << logger::endl;
            return 1;
        }

        if (FD_ISSET(self_, &readfds)) {
            if ((new_socket = accept(self_, (struct sockaddr *) &address, (int *) &addrlen)) < 0) {
                log(constants::logger, info)
                        << "accept"
                        << logger::endl;
            }

            log(constants::logger, info)
                    << "New peer connected at "
                    << inet_ntoa(address.sin_addr)
                    << ':'
                    << ntohs(address.sin_port)
                    << logger::endl;

            // send the welcome message
            std::string welcome = "0x01\r\n";
            if (send(new_socket, welcome.c_str(), welcome.size(), 0) != welcome.size()) {
                log(constants::logger, error)
                        << "Send failed"
                        << logger::endl;
            }

            log(constants::logger, info)
                    << "Welcome message sent successfully"
                    << logger::endl;

            for (int i = 0; i < CONNECT_MAX; ++i) {
                if (clients_[i] == 0) {
                    clients_[i] = new_socket;
                    log(constants::logger, info)
                            << "Adding  to list of sockets at index "
                            << i
                            << logger::endl;
                    break;
                }
            }
        }
        for (auto[i, s] = std::tuple{0, SOCKET()}; i < CONNECT_MAX; ++i) {
            s = clients_[i];
            if (FD_ISSET(s, &readfds)) {
                getpeername(s, (struct sockaddr *) &address, (int *) &addrlen);
                int valread = recv(s, buffer, MAXRECV, 0);

                if (valread == SOCKET_ERROR) {
                    int error_code = WSAGetLastError();
                    if (error_code == 10054) {
                        log(constants::logger, warning)
                                << "disconnected unexpectedly, ip "
                                << inet_ntoa(address.sin_addr)
                                << ", port "
                                << ntohs(address.sin_port)
                                << logger::endl;

                        closesocket(s);
                        clients_[i] = 0;
                    } else {
                        log(constants::logger, error)
                                << "recv failed: "
                                << error_code;
                    }
                }

                if (valread == 0) {
                    log(constants::logger, info)
                            << "Host disconnected, ip "
                            << inet_ntoa(address.sin_addr)
                            << ", port "
                            << ntohs(address.sin_port)
                            << logger::endl;

                    closesocket(s);
                    clients_[i] = 0;
                } else {
                    buffer[valread] = '\0';
                    buffer = util::remove(buffer, '\n');
                    buffer = util::remove(buffer, '\r');
                    std::cout << buffer;
                    log(constants::logger, debug)
                            << inet_ntoa(address.sin_addr)
                            << ':'
                            << ntohs(address.sin_port)
                            << "-> "
                            << buffer
                            << logger::endl;
                    send(s, buffer, strlen(buffer), 0);
                }
            }
        }
    }
//
//    closesocket(s);
//    WSACleanup();
//
//    return 0;
}
