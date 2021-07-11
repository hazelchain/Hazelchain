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

using namespace std;
using namespace boost::multiprecision;

namespace util {
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
}

#endif //HAZELCHAIN_UTIL_H
