//
// Created by chris on 2021-07-16.
//

#ifndef HAZELCHAIN_STRUTIL_H
#define HAZELCHAIN_STRUTIL_H

#include <utility>

#include "Math.h"

namespace util {
    inline std::string string_of(char c, int amount);

    inline std::string reverse(std::string in);

    inline math::uint256_t stringToInt(const std::string &in);

    template<class T>
    inline std::string to_string(const T &in);

    inline bool isGreaterThan(const std::string &a, const std::string &b);

    inline const char *concat(const char *a, const char *b);

    inline std::string concat(const std::string &a, const std::string &b);

    inline std::string concat(std::initializer_list<std::string> in);

    inline bool contains(const char *str, const char *word);

    inline bool contains(const std::initializer_list<char *> &arr, const char *find);

    inline bool contains(int size, char **arr, const char *find);

    inline char *remove(std::string str, char c);


    template<class T>
    inline std::string vectorToString(std::vector<T> in);

    inline std::string replace(std::string in, const std::string &a, const std::string &b);

    inline std::vector<std::string> split(const std::string &in, char a);

    inline int count_of(const std::string &in, char a);

    inline std::string string_of(char c, int amount) {
        std::stringstream ss;
        for (int i = 0; i < amount; ++i) ss << c;
        return ss.str();
    }

    inline std::string reverse(std::string in) {
        for (size_t i = 0, n = in.length(); i < n / 2; ++i)
            std::swap(in[i], in[n - i - 1]);
        return in;
    }

    inline math::uint256_t stringToInt(const std::string &in) {
        std::string inr = reverse(in);
        math::uint256_t out = 0;
        for (long i = 0; i < inr.size(); ++i) {
            out += static_cast<math::uint256_t>(inr[i] * pow(10, i));
        }
        return out;
    }

    template<class T>
    inline std::string to_string(const T &in) {
        std::stringstream ss;
        ss << in;
        return ss.str();
    }

    inline bool isGreaterThan(const std::string &a, const std::string &b) {
        if (a.size() > b.size()) return true;
        if (a.size() < b.size()) return false;
        math::uint256_t ad = stringToInt(a);
        math::uint256_t bd = stringToInt(b);
        return ad > bd;
    }

    inline const char *concat(const char *a, const char *b) {
        unsigned long al = strlen(a);
        unsigned long bl = strlen(b);
        char *result = new char[al + bl + 1];
        std::copy(a, a + al, result);
        std::copy(b, b + bl, result + al);
        result[al + bl] = '\0';
        return result;
    }

    inline std::string concat(const std::string &a, const std::string &b) {
        std::stringstream ss;
        ss << a << b;
        return ss.str();
    }

    inline std::string concat(std::initializer_list<std::string> in) {
        std::stringstream ss;

        for (const std::string &p: in) {
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

    inline bool contains(const std::initializer_list<char *> &arr,
                         const char *find) {
        return std::any_of(arr.begin(), arr.end(), [find](char *x) {
            return contains(x, find);
        });
    }

    inline bool contains(int size, char **arr, const char *find) {
        return std::any_of(arr, arr + size, [find](char *x) {
            return contains(x, find);
        });
    }

    template<class T>
    inline std::string vectorToString(std::vector<T> in) {
        return std::string{in.begin(), in.end()};
    }

    inline std::string replace(std::string in, const std::string &a, const std::string &b) {
        for (int i = 0; i < (in.size() - a.size()); i++) {
            if (in.substr(i, a.size()) == a) {
                std::stringstream ss;
                ss << in.substr(0, i) << b << in.substr(i + a.size(),
                                                        in.size());
                in = ss.str();
            }
        }
        return in;
    }

    inline std::vector<std::string> split(const std::string &in, const char a) {
        std::vector<std::string> out;
        std::string left = in;
        int total = count_of(in, a);
        for (int i = 0; i < total; ++i) {
            for (int j = 0; j < left.size(); ++j) {
                if (left.at(j) == a) {
                    out.push_back(left.substr(0, j));
                    left = left.substr(j + 1);
                    break;
                }
            }
        }
        out.push_back(left);
        return out;
    }

    inline int count_of(const std::string &in, const char a) {
        int t = 0;
        for (char i: in) if (i == a) ++t;
        return t;
    }

    inline char *remove(std::string str, char c) {
        str.erase(std::remove(str.begin(), str.end(), c), str.end());
        return const_cast<char *>(str.c_str());
    }
}

#endif //HAZELCHAIN_STRUTIL_H
