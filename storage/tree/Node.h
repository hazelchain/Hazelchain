//
// Created by chris on 2021-06-28.
//

#ifndef FLAMECOIN_NODE_H
#define FLAMECOIN_NODE_H

#include <cstring>
#include <sstream>
#include "../../lib/sha256/sha256.h"

using namespace std;

template<class Type>
class Node {
public:
    string hash;
    Type data;
    Node *left;
    Node *right;

    Node(const Type &data) {
        this->data = data;
        this->right = nullptr;
        this->left = nullptr;
    }

    void Hash() {
        stringstream ss;
        // TODO: Make all Item classes derive from a class that has a to_string() function
        if (left) ss << this->left->hash;
        if (right) ss << this->right->hash;
        this->hash = sha256(ss.str());
    }
};


#endif //FLAMECOIN_NODE_H
