//
// Created by chris on 2021-07-12.
//

#include <utility>
#include <fstream>
#include "Logger.h"
#include "../../util/util.h"

using namespace std;

string parseLevel(Level in) {
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

//void Logger::_log() const {
//    if (!bLog) return;
//    ofstream out;
//    out.open(location_, ios_base::app);
//
//    string p;
//    switch (debug_level_) {
//        case debug:
//            p = "[debug] ";
//            break;
//        case error:
//            p = "[error] ";
//            break;
//        case warning:
//            p = "[warning] ";
//            break;
//        case info:
//            p = "[info] ";
//            break;
//    }
//
//    out << util::currentTime("[%d:%m:%y  %H:%M:%S] ") << p << stream_;
//    out.close();
//}

Logger::Logger() = default;

Logger::Logger(string location, ostream &stream)
        : location_(move(location)), stream_(&stream) {
}

Logger &Logger::operator<<(const string &msg) {
    *stream_ << msg;
    return *this;
}

Logger &Logger::operator<<(char c) {
    *stream_ << c;
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