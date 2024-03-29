//
// Created by chris on 2021-06-28.
//

#ifndef HAZELCHAIN_UTIL_H
#define HAZELCHAIN_UTIL_H

#include <dirent.h>
#include <chrono>
#include "../Transaction.h"
#include "../storage/tree/TransactionTree.h"
#include "../Block.h"
#include "Http.h"
#include "strutil.h"

using json = nlohmann::json;

namespace util {
    inline bool exists(const char *in);

    inline std::string generateGenesisHash();

    inline std::string getIp();

    inline std::string currentTime(const char *fmt);

    inline bool contains(const std::map<std::string, std::string> &in, const std::string &key);

    inline json loadJson(const std::string &file, json target);


    inline bool exists(const char *in) {
        DIR *t = opendir(in);
        if (!t) {
            closedir(t);
            return false;
        }
        closedir(t);
        return true;
    }

    inline std::string generateGenesisHash() {
        // TODO: set the timestamp to the day this is released
        return Block(
                {
                        Transaction("genesis",
                                    "christian",
                                    50000000),
                        Transaction("genesis",
                                    "justin",
                                    50000000),
                        Transaction("genesis",
                                    "charity",
                                    100000000),
                        Transaction("genesis",
                                    "dev",
                                    100000000),
                },
                1222660800
        ).getHash();
    }

    inline std::string getIp() {
//        return requests::GET("requests://api.ipify.org").response;
        return "unimplemented";
    }

    inline std::string currentTime(const char *fmt) {
        char buffer[256];
        const time_t t = time(nullptr);
        strftime(buffer, sizeof(buffer), fmt, localtime(&t));
        return buffer;
    }

    inline bool contains(const std::map<std::string, std::string> &in, const std::string &key) {
        for (auto &i : in) {
            if (i.first == key) return true;
        }
        return false;
    }

    inline json loadJson(const std::string &file, json target) {
        std::ifstream ifs("settings.json");
        if (ifs.bad() || ifs.peek() == std::ifstream::traits_type::eof())
            return target;

        json current = json::parse(ifs);
        for (auto&[k, v] : target.items())
            if (current.find(k) == current.end()) current[k] = v;
        return current;
    }
}

#endif //HAZELCHAIN_UTIL_H
