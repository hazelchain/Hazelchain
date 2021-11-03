//
// Created by chris on 2021-10-15.
//

#ifndef HAZELCHAIN_SOCKUTIL_H
#define HAZELCHAIN_SOCKUTIL_H

#ifdef WIN32

namespace util {
    inline void initWSA() {
        WSAData wsa{};
        if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
            log(constants::logger, error)
                    << "Failed to load server: "
                    << WSAGetLastError
                    << std::endl;
            exit(1);
        }
    }

    inline std::vector<std::string> ipsOf(const std::string &domain) {
#ifdef WIN32
        util::initWSA();
#endif
        hostent *h = gethostbyname(domain.c_str());
        if (h == nullptr) {
            log(constants::logger, error)
                    << "could not get ips from "
                    << domain
                    << ": "
                    << WSAGetLastError()
                    << std::endl;
        }

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

#endif

#endif //HAZELCHAIN_SOCKUTIL_H
