//
// Created by chris on 2021-07-12.
//

#ifndef HAZELCHAIN_LOGGER_H
#define HAZELCHAIN_LOGGER_H

#include <string>
#include <sstream>
#include <vector>
#include "../../util/util.h"
#include "../../util/strutil.h"

using namespace std;

enum Level {
    debug,
    error,
    warning,
    info
};

class Logger {
    ostream *stream_;
    Level debug_level_ = info;
    string location_;
public:

    Logger();

    Logger(string location, ostream &stream);

    Logger &operator<<(const string &msg);

    Logger &operator<<(char c);

    friend Logger &log(Logger &logger, Level lvl);
};


#endif //HAZELCHAIN_LOGGER_H
