//
// Created by chris on 2021-07-12.
//

#ifndef HAZELCHAIN_LOGGER_H
#define HAZELCHAIN_LOGGER_H

#include <string>
#include <ostream>
#include <winsock2.h>
#include <mutex>
#include <syncstream>
#include "../../util/util.h"
#include "../../util/strutil.h"

enum Level {
    debug,
    error,
    warning,
    info
};

inline std::string parseLevel(Level in) {
    switch (in) {
        case debug:
            return "[debug]";
        case error:
            return "[error]";
        case warning:
            return "[warning]";
        case info:
            return "[info]";
        default:
            return "[info]";
    }
}

class Logger {
    static std::mutex mtx_;
    std::ostream *stream_ = &std::cout;
    std::string location_ = util::concat(
            util::currentTime("[%d-%m-%y  %H:%M:%S] "),
            "-log.txt"
    );

public:
    Logger() = default;

    Logger(std::string location, std::ostream &stream)
            : location_(move(location)), stream_(&stream) {
    }

    template<class T>
    Logger &operator<<(T c) {
//        mtx_.lock();
        *stream_ << c;
//        mtx_.unlock();
        return *this;
    }

    friend std::osyncstream log(Logger &logger, Level lvl) {
        std::osyncstream oss(*logger.stream_);
        oss << util::currentTime("[%d:%m:%y  %H:%M:%S] ")
            << parseLevel(lvl)
            << " ";
        return oss;
    }
};


#endif //HAZELCHAIN_LOGGER_H
