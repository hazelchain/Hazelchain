//
// Created by chris on 2021-08-08.
//

#ifndef HAZELCHAIN_SHA256_H
#define HAZELCHAIN_SHA256_H

#include <openssl/sha.h>
#include <string>

using namespace std;

namespace util {
    inline string sha256(const string &in) {
        unsigned char buffer[8192];
        unsigned char output[SHA256_DIGEST_LENGTH];
        size_t len;

        SHA256_CTX sha;
        SHA256_Init(&sha);
        SHA256_Update(&sha, buffer, sizeof len);
        SHA256_Final(output, &sha);

        char p[SHA256_DIGEST_LENGTH];

        for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
            p[i] = output[i];
        }

        string o(p);
        return o;
    }
}
#endif //HAZELCHAIN_SHA256_H
