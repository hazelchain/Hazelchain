//
// Created by chris on 2021-07-17.
//

#ifndef HAZELCHAIN_CONFUTIL_H
#define HAZELCHAIN_CONFUTIL_H

namespace util {
    map<string, string> parseConf(const char *file);

    map<string, string> parseConf(const char *file) {
//        map<string, string> out;
//        ifstream ifs(file);
//        if (ifs.is_open()) {
//            string line;
//            while (getline(ifs, line)) {
//                line = replace(line, " ", "");
//                string *chars = split(line, '=');
//
//            }
//        } else throw FileNotFoundException(ifs);
    }

}

#endif //HAZELCHAIN_CONFUTIL_H
