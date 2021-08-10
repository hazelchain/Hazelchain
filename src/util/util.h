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

using namespace std;
using json = nlohmann::json;

namespace util {
    inline bool exists(const char *in);

    inline string generateGenesisHash();

    inline string getIp();

    inline string currentTime(const char *fmt);

    inline bool contains(const map<string, string> &in, const string &key);

    inline json loadJson(const string &file);


    inline bool exists(const char *in) {
        DIR *t = opendir(in);
        if (!t) {
            closedir(t);
            return false;
        }
        closedir(t);
        return true;
    }

    inline string generateGenesisHash() {
        vector<Transaction *> tx{
                new Transaction("", "christian", 100),
                new Transaction("", "justin", 100),
                new Transaction("", "charity", 100),
        };
        Block gen(tx, 979516800);
        return gen.getHash();
    }

    inline string getIp() {
        return requests::GET("requests://api.ipify.org").response;
    }

    inline string currentTime(const char *fmt) {
        char buffer[256];
        const time_t t = time(nullptr);
        strftime(buffer, sizeof(buffer), fmt, localtime(&t));
        return buffer;
    }

    inline bool contains(const map<string, string> &in, const string &key) {
        for (auto &i : in) {
            if (i.first == key) return true;
        }
        return false;
    }

    inline json loadJson(const string &file) {
        ifstream ifs("settings.json");
        if (ifs.good()) {
            if (ifs.peek() == std::ifstream::traits_type::eof()) {
                return {{"bad", true}};
            }
            return json::parse(ifs);
        }
        return {{"bad", true}};
    }
}

#endif //HAZELCHAIN_UTIL_H
