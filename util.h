//
// Created by chris on 2021-06-28.
//

#ifndef HAZELCHAIN_UTIL_H
#define HAZELCHAIN_UTIL_H

#include <bits/stdc++.h>
#include <boost/multiprecision/cpp_int.hpp>
#include <dirent.h>
#include "Transaction.h"
#include "storage/tree/TransactionTree.h"
#include "Block.h"
#include "libs/httpRequests/http.hpp"

using namespace std;
using namespace boost::multiprecision;

namespace util {
    inline string string_of(char c, int amount);
    inline string reverse(string in);
    inline uint1024_t stringToInt(const string &in);
    inline bool isGreaterThan(const string &a, const string &b);
    inline const char *concat(const char *a, const char *b);
    inline bool exists(const char *in);
    inline string generateGenesisHash();
    inline bool contains(const char *str, const char *word);
    inline bool contains(const initializer_list<char *> &arr, const char *find);
    template<class T> inline string vectorToString(vector<T> in);
    inline string getIp();
    namespace req {
        inline http::Response get(const char *ip);
    }

    inline string string_of(char c, int amount) {
        stringstream ss;
        for (int i = 0; i < amount; ++i) ss << c;
        return ss.str();
    }

    inline string reverse(string in) {
        for (auto [i, n] = tuple(0, in.length()); i < n / 2; ++i) swap(in[i], in[n - i - 1]);
        return in;
    }

    inline uint1024_t stringToInt(const string &in) {
        string inr = reverse(in);
        uint1024_t out = 0;
        for (long long i = 0; i < inr.size(); ++i) {
            out += static_cast<uint1024_t>(inr[i]  *pow(10, i));
        }
        return out;
    }

    inline bool isGreaterThan(const string &a, const string &b) {
        if (a.size() > b.size()) return true;
        if (a.size() < b.size()) return false;
        uint1024_t ad = stringToInt(a);
        uint1024_t bd = stringToInt(b);
        return ad > bd;
    }

    inline const char *concat(const char *a, const char *b) {
        unsigned long al = strlen(a);
        unsigned long bl = strlen(b);
        char *result = new char[al + bl + 1];
        copy(a, a + al, result);
        copy(b, b + bl, result + al);
        result[al + bl] = '\0';
        return result;
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

    inline bool contains(const char *str, const char *word) {
        size_t sl = strlen(str), wl = strlen(word);
        size_t i = 0;
        do {
            int total = 0;
            for (int j = 0; j < wl; ++j) {
                if (str[i + j] == word[j]) ++total;
            }
            if (total == wl) {
                return true;
            }
        } while ((i += 1) < sl - wl);
        return false;
    }
    inline bool contains(const initializer_list<char *> &arr, const char *find) {
        return any_of(arr.begin(), arr.end(), [find](char *x) {
            return contains(x, find);
        });
    }
    inline bool contains(int size, char **arr, const char *find) {
        return any_of(arr, arr + size, [find](char *x) {
            return contains(x, find);
        });
    }

    template<class T> inline string vectorToString(vector<T> in) {
        return string{in.begin(), in.end()};
    }

    inline string getIp() {
        string out = vectorToString<uint8_t>(req::get("http://api.ipify.org").body);
        return out;
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
