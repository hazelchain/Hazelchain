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
                    << "Failed to load server"
                    << std::endl;
            exit(1);
        }
    }
}

#endif

#endif //HAZELCHAIN_SOCKUTIL_H
