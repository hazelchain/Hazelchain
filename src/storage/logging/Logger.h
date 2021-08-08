//
// Created by chris on 2021-07-12.
//

#ifndef HAZELCHAIN_LOGGER_H
#define HAZELCHAIN_LOGGER_H

#include <string>

using namespace std;

class Logger {
public:
    bool bShow;
    bool bLog;

    Logger();

    explicit Logger(string locationIn);

    void log(const string &in);

    void log(const initializer_list<string> &in);

private:
    string location_;

    void _log(const string &in) const;

    void _show(const string &in) const;
};


#endif //HAZELCHAIN_LOGGER_H
