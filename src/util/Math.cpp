//
// Created by chris on 2021-08-08.
//

#include <cstdio>
#include <algorithm>
#include "Math.h"

math::BigInt::BigInt(unsigned int in) {
    zero();
    set(in);
}

math::BigInt::BigInt(int in) {
    zero();
    set(in);
}

math::BigInt::BigInt(unsigned long in) {
    zero();
    set(in);
}

math::BigInt::BigInt(long in) {
    zero();
    set(in);
}

math::BigInt::BigInt(double in) {
    zero();
    set(in);
}

void math::BigInt::zero() {
    for (unsigned long i = 0; i < length; ++i) {
        digits[i] = 0;
    }
}

void math::BigInt::set(unsigned int in) {
    vector<unsigned int> p = num_to_arr(in);
    for (size_t i = p.size(); i > 0; --i) {
        digits[i + (length - p.size())] = p.at(i);
    }
}

vector<unsigned int> math::BigInt::num_to_arr(unsigned long long in) {
    vector<unsigned int> out;
    while (in > 1) {
        out.push_back(in % 10);
        in = in / 10;
    }
    reverse(out.begin(), out.end());
    return out;
}

bool math::BigInt::operator<(math::BigInt other) {
    for (unsigned long i = length - 1; i > 0; --i) {
        if (digits[i] < other.digits[i]) return true;
        if (digits[i] > other.digits[i]) return false;
    }

    return false;
}

bool math::BigInt::operator>(math::BigInt other) {
    for (unsigned long i = length - 1; i > 0; --i) {
        if (digits[i] > other.digits[i]) return true;
        if (digits[i] < other.digits[i]) return false;
    }

    return false;
}

math::BigInt &math::BigInt::operator++() {
    add(1);
    return *this;
}

void math::BigInt::add(unsigned int value) {
    add_recurse(value, length - 1);
}

void math::BigInt::add(math::BigInt value) {
    add_recurse(value, 0, length - 1);
}

void math::BigInt::add_recurse(unsigned int carry, unsigned long index) {
    if (index < 0) return;

    int p = digits[index] + carry;
    if (p > 9) {
        digits[index] = p % 10;
        p /= 10;
        add_recurse(p, --index);
    }
}

void math::BigInt::add_recurse(math::BigInt other, unsigned int carry, unsigned long index) {
    if (index < 0) return;

    int p = digits[index] + other.digits[index];
    if (p > 9) {
        digits[index] = p % 10;
        p /= 10;
        add_recurse(other, p, --index);
    }
}

math::BigInt &math::BigInt::operator+=(math::BigInt other) {
    add(other);
    return *this;
}
