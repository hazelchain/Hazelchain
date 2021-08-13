//
// Created by chris on 2021-08-08.
//

#ifndef HAZELCHAIN_SHA256_H
#define HAZELCHAIN_SHA256_H

#include <openssl/sha.h>
#include <cstring>

namespace util {
    inline void sha256_string(const char *string, char outputBuffer[65]) {
        unsigned char hash[SHA256_DIGEST_LENGTH];
        SHA256_CTX sha256;
        SHA256_Init(&sha256);
        SHA256_Update(&sha256, string, std::strlen(string));
        SHA256_Final(hash, &sha256);
        int i;
        for (i = 0; i < SHA256_DIGEST_LENGTH; i++) {
            sprintf(outputBuffer + (i * 2), "%02x", hash[i]);
        }
        outputBuffer[64] = 0;
    }

    inline std::string sha256(const std::string &in) {
        char buffer[65];
        sha256_string(in.c_str(), buffer);
        std::string o(buffer);
        return o;
    }
}
#endif //HAZELCHAIN_SHA256_H
