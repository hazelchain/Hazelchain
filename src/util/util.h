//
// Created by chris on 2021-06-28.
//

#ifndef HAZELCHAIN_UTIL_H
#define HAZELCHAIN_UTIL_H

#include <bits/stdc++.h>
#include <dirent.h>
#include "../Transaction.h"
#include "../storage/tree/TransactionTree.h"
#include "../Block.h"
#include "../libs/httpRequests/http.hpp"
#include "strutil.h"

using namespace std;
using namespace boost::multiprecision;
using namespace boost;

namespace util {
    inline bool exists(const char *in);
    inline string generateGenesisHash();
    inline string getIp();
    inline string currentTime(const char *fmt);
    inline bool contains(map<string, string> in, const string &key);

    namespace req {
        inline http::Response get(const char *ip);
    }

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
        string out = vectorToString<uint8_t>(
                req::get("http://api.ipify.org").body);
        return out;
    }

    inline string currentTime(const char *fmt) {
        char buffer[256];
        const time_t t = time(nullptr);
        strftime(buffer, sizeof(buffer), fmt, localtime(&t));
//        buffer[255] = '\0';
        return buffer;
    }

    inline bool contains(map<string, string> in, const string &key) {
        for (map<string, string>::iterator i = in.begin(); i != in.end(); ++i) {
            if (i->first == key) return true;
        }
        return false;
    }

    namespace req {
        inline http::Response get(const char *ip) {
            http::Request req{ip};
            const auto response = req.send("GET");
            return response;
        }
    }
}

#endif //HAZELCHAIN_UTIL_H
