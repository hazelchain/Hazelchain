//
// Created by chris on 2021-07-16.
//

#ifndef HAZELCHAIN_STRUTIL_H
#define HAZELCHAIN_STRUTIL_H

#include <boost/multiprecision/cpp_int.hpp>

using namespace std;
using namespace boost::multiprecision;
using namespace boost;

namespace util {
    inline string string_of(char c, int amount);
    inline string reverse(string in);
    inline uint1024_t stringToInt(const string &in);
    template<class T> inline string to_string(const T &in);
    inline bool isGreaterThan(const string &a, const string &b);
    inline const char *concat(const char *a, const char *b);
    inline string concat(const string &a, const string &b);
    inline string concat(initializer_list<string> in);
    inline bool contains(const char *str, const char *word);
    inline bool contains(const initializer_list<char *> &arr, const char *find);
    inline bool contains(int size, char **arr, const char *find);
    template<class T> inline string vectorToString(vector<T> in);


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

    template<class T> inline string to_string(const T &in) {
        stringstream ss;
        ss << in;
        return ss.str();
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

    inline string concat(const string &a, const string &b) {
        stringstream ss;
        ss << a << b;
        return ss.str();
    }

    inline string concat(initializer_list<string> in) {
        stringstream ss;

        for (string p : in) {
            ss << p;
        }

        return ss.str();
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
}

#endif //HAZELCHAIN_STRUTIL_H
