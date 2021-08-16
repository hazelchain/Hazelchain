//
// Created by chris on 2021-07-12.
//

#ifndef HAZELCHAIN_LOGGER_H
#define HAZELCHAIN_LOGGER_H

#include <string>
#include <ostream>
#include <winsock2.h>

enum Level {
    debug,
    error,
    warning,
    info
};

namespace logger {
    inline std::string endl = "\r\n";
}

class Logger {
    std::ostream *stream_;
    Level debug_level_ = info;
    std::string location_;

public:
    Logger();

    Logger(std::string location, std::ostream &stream);

    Logger &operator<<(const std::string &msg);

    Logger &operator<<(int c);

    Logger &operator<<(char c);

    Logger &operator<<(double c);

    Logger &operator<<(unsigned long long c);

    friend Logger &log(Logger &logger, Level lvl);
};


#endif //HAZELCHAIN_LOGGER_H
