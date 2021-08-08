//
// Created by chris on 2021-07-16.
//

#ifndef HAZELCHAIN_STRUTIL_H
#define HAZELCHAIN_STRUTIL_H

#include "Math.h"

using namespace std;
using namespace math;

namespace util {
    inline string string_of(char c, int amount);

    inline string reverse(string in);

    inline uint256_t stringToInt(const string &in);

    template<class T>
    inline string to_string(const T &in);

    inline bool isGreaterThan(const string &a, const string &b);

    inline const char *concat(const char *a, const char *b);

    inline string concat(const string &a, const string &b);

    inline string concat(initializer_list<string> in);

    inline bool contains(const char *str, const char *word);

    inline bool contains(const initializer_list<char *> &arr, const char *find);

    inline bool contains(int size, char **arr, const char *find);

    template<class T>
    inline string vectorToString(vector<T> in);

    inline string replace(string in, const string &a, const string &b);

    inline vector<string> split(const string &in, const char a);

    inline int count_of(const string &in, const char a);


    inline string string_of(char c, int amount) {
        stringstream ss;
        for (int i = 0; i < amount; ++i) ss << c;
        return ss.str();
    }

    inline string reverse(string in) {
        for (size_t i = 0, n = in.length(); i < n / 2; ++i)
            swap(in[i], in[n - i - 1]);
        return in;
    }

    inline uint256_t stringToInt(const string &in) {
        string inr = reverse(in);
        uint256_t out = 0;
        for (long i = 0; i < inr.size(); ++i) {
            out += static_cast<uint256_t>(inr[i] * pow(10, i));
        }
        return out;
    }

    template<class T>
    inline string to_string(const T &in) {
        stringstream ss;
        ss << in;
        return ss.str();
    }

    inline bool isGreaterThan(const string &a, const string &b) {
        if (a.size() > b.size()) return true;
        if (a.size() < b.size()) return false;
        uint256_t ad = stringToInt(a);
        uint256_t bd = stringToInt(b);
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

        for (const string &p : in) {
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

    inline bool contains(const initializer_list<char *> &arr,
                         const char *find) {
        return any_of(arr.begin(), arr.end(), [find](char *x) {
            return contains(x, find);
        });
    }

    inline bool contains(int size, char **arr, const char *find) {
        return any_of(arr, arr + size, [find](char *x) {
            return contains(x, find);
        });
    }

    template<class T>
    inline string vectorToString(vector<T> in) {
        return string{in.begin(), in.end()};
    }

    inline string replace(string in, const string &a, const string &b) {
        for (int i = 0; i < (in.size() - a.size()); i++) {
            if (in.substr(i, a.size()) == a) {
                stringstream ss;
                ss << in.substr(0, i) << b << in.substr(i + a.size(),
                                                        in.size());
                in = ss.str();
            }
        }
        return in;
    }

    inline vector<string> split(const string &in, const char a) {
        vector<string> out;
        string left = in;
        int total = count_of(in, a);
        for (int i = 0; i < total; ++i) {
            for (int j = 0; j < left.size(); ++j) {
                if (left.at(j) == a) {
                    out.push_back(left.substr(0, j));
                    left = left.substr(j + 1);
                    break;
                }
            }
            if (i == (total - 1)) {
                out.push_back(left);
                break;
            }
        }
        return out;
    }

    inline int count_of(const string &in, const char a) {
        int t = 0;
        for (int i = 0; i < in.size(); ++i) if (in.at(i) == a) ++t;
        return t;
    }
}

#endif //HAZELCHAIN_STRUTIL_H
