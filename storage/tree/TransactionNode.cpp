//
// Created by chris on 2021-06-30.
//

#include "TransactionNode.h"

TransactionNode::TransactionNode(const Transaction &data) : data(data) {
    this->right = nullptr;
    this->left = nullptr;
}
TransactionNode::TransactionNode(Transaction *data) : data(data) {
    this->right = nullptr;
    this->left = nullptr;
}

void TransactionNode::Hash() {
    stringstream ss;
    ss << data.to_string();
    if (left) ss << left->hash;
    if (right) ss << right->hash;
    this->hash = sha256(ss.str());
}
