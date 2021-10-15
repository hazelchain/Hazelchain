//
// Created by chris on 2021-06-28.
//

#ifndef HAZELCHAIN_UTIL_H
#define HAZELCHAIN_UTIL_H

#include <dirent.h>
#include <chrono>
#include <winsock2.h>
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

    template<size_t S>
    inline int firstZero(std::array<SOCKET, S> arr, int size);

    template<size_t X, size_t Y>
    inline bool isEmpty(std::array<std::array<SOCKET, Y>, X> arr);

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
                        Transaction(
                                "genesis",
                                "christian",
                                50000000),
                        Transaction(
                                "genesis",
                                "justin",
                                50000000),
                        Transaction(
                                "genesis",
                                "charity",
                                100000000),
                        Transaction(
                                "genesis",
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
        for (auto &i: in) {
            if (i.first == key) return true;
        }
        return false;
    }

    inline json loadJson(const std::string &file, json target) {
        std::ifstream ifs("settings.json");
        if (ifs.bad() || ifs.peek() == std::ifstream::traits_type::eof())
            return target;

        json current = json::parse(ifs);
        for (auto[k, v]: target.items())
            if (current.find(k) == current.end()) current[k] = v;
        return current;
    }

    template<size_t S>
    inline int firstZero(std::array<SOCKET, S> arr, int size) {
        for (int i = 0; i < size; ++i) {
            if (arr[i] == 0) return i;
        }
        return -1;
    }

    template<size_t Y>
    inline bool isEmpty(std::array<SOCKET, Y> arr) {
        for (int i = 0; i < Y; ++i) {
            if (arr[i] != 0) return false;
        }
        return true;
    }

    template<typename V>
    inline std::vector<V> join(std::initializer_list<std::vector<V>> vecs) {
        std::vector<V> total;
        for (std::vector vec: vecs) {
            std::vector<V> both;
            both.reserve(total.size() + vec.size());
            both.insert(both.end(), total.begin(), total.end());
            both.insert(both.end(), vec.begin(), vec.end());
            total = both;
        }
        return total;
    }
}

#endif //HAZELCHAIN_UTIL_H
