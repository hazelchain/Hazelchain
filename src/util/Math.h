//
// Created by chris on 2021-08-07.
//

#ifndef HAZELCHAIN_MATH_H
#define HAZELCHAIN_MATH_H

#include <vector>

using namespace std;

namespace math {
    class BigInt {
        const long length = 32;
        int digits[32] = {0};

    public:
        BigInt(unsigned int in);

        BigInt(int in);

        BigInt(unsigned long in);

        BigInt(long in);

        BigInt(double in);

        bool operator<(BigInt other);

        bool operator>(BigInt other);

        BigInt &operator++();

        BigInt &operator+=(BigInt other);

    private:
        void zero();

        void set(unsigned int in);

        void add(unsigned int value);

        void add(BigInt value);

        void add_recurse(unsigned int carry, unsigned long index);

        void add_recurse(BigInt other, unsigned int carry, unsigned long index);

        static vector<unsigned int> num_to_arr(unsigned long long in);
    };

    typedef BigInt uint256_t;
}

#endif //HAZELCHAIN_MATH_H