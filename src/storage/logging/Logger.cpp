//
// Created by chris on 2021-07-12.
//

#include <utility>
#include <iostream>
#include "Logger.h"
#include "../../util/util.h"

std::string parseLevel(Level in) {
    switch (in) {
        case debug:
            return "[debug]";
        case error:
            return "[error]";
        case warning:
            return "[warning]";
        case info:
            return "[info]";
    }
    return "[info]";
}

Logger::Logger() = default;

Logger::Logger(std::string location, std::ostream &stream)
        : location_(move(location)), stream_(&stream) {
}

Logger &Logger::operator<<(const std::string &msg) {
    *stream_ << msg;
    return *this;
}

Logger &Logger::operator<<(int c) {
    *stream_ << c;
    return *this;
}

Logger &Logger::operator<<(char c) {
    *stream_ << c;
    return *this;
}

Logger &Logger::operator<<(double c) {
    *stream_ << c;
    return *this;
}

Logger &Logger::operator<<(SOCKET c) {
    *stream_ << c;
    return *this;
}

Logger &Logger::operator<<(std::ostream &(*pManip)(std::ostream &)) {
    *stream_ << pManip;
    return *this;
}

Logger &log(Logger &logger, Level lvl) {
    logger.debug_level_ = lvl;
    *logger.stream_
            << util::currentTime("[%d:%m:%y  %H:%M:%S] ")
            << parseLevel(lvl)
            << " ";
    return logger;
}
