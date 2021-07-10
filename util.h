//
// Created by chris on 2021-06-28.
//

#ifndef FLAMECOIN_UTIL_H
#define FLAMECOIN_UTIL_H

#include <bits/stdc++.h>
#include <boost/multiprecision/cpp_int.hpp>
#include <dirent.h>
#include "Transaction.h"
#include "storage/tree/TransactionTree.h"

using namespace std;

namespace util {
    template<typename T>
    inline const string toString(const T &t) {
        std::ostringstream oss;
        oss << t;
        return oss.str();
    }

    inline const string string_of(char c, int amount) {
        stringstream ss;
        for (int i = 0; i < amount; ++i) ss << c;
        return ss.str();
    }

    inline const string reverse(string in) {
        int n = in.length();
        for (int i = 0; i < n / 2; i++) swap(in[i], in[n - i - 1]);
        return in;
    }

    inline const boost::multiprecision::uint1024_t stringToInt(const string &in) {
        string inr = reverse(in);
        boost::multiprecision::uint1024_t out = 0;
        for (long long i = 0; i < inr.size(); ++i) {
            out += static_cast<boost::multiprecision::uint1024_t>(inr[i]  *pow(10, i));
        }
        return out;
    }

    inline const bool isGreaterThan(const string &a, const string &b) {
        if (a.size() > b.size()) return true;
        if (a.size() < b.size()) return false;
        boost::multiprecision::uint1024_t ad = stringToInt(a);
        boost::multiprecision::uint1024_t bd = stringToInt(b);
        return ad > bd;
    }

    inline const char *concat(const char *a, const char *b) {
        int al = strlen(a);
        int bl = strlen(b);
        char *result = new char[al + bl + 1];
        copy(a, a + al, result);
        copy(b, b + bl, result + al);
        result[al + bl] = '\0';
        return result;
    }

    bool exists(const char *in) {
        DIR *t = opendir(in);
        if (!t) {
            closedir(t);
            return false;
        }
        closedir(t);
        return true;
    }
}

#endif //FLAMECOIN_UTIL_H
