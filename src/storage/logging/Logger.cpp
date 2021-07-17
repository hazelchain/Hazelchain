//
// Created by chris on 2021-07-12.
//

#include <utility>
#include <fstream>
#include "Logger.h"
#include "../../util/util.h"

using namespace std;

Logger::Logger() {
    bShow = true;
    bLog = false;
    location_ = "";
}

Logger::Logger(string locationIn) : location_(std::move(locationIn)) {
    bShow = true;
    bLog = true;
}

void Logger::log(const string &in) {
    _log(in);
    _show(in);
}

void Logger::log(const initializer_list<string> &in) {
    string p = util::concat(in);
    _log(p);
    _show(p);
}

void Logger::_log(const string &in) const {
    if (!bLog) return;
    ofstream out;
    out.open(location_, ios_base::app);
    out << util::concat(util::currentTime("[%d-%m-%y  %H:%M:%S] "), in);
    out.close();
}

void Logger::_show(const string &in) const {
    if (!bShow) return;
    cout << in << endl;
}
