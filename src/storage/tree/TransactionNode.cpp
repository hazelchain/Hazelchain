//
// Created by chris on 2021-06-30.
//

#include "TransactionNode.h"
#include "../../util/sha256.h"
#include <sha256.h>

TransactionNode::TransactionNode(Transaction data) : tData(std::move(data)) {
    this->right = nullptr;
    this->left = nullptr;
}

TransactionNode::TransactionNode(const Transaction *data) : tData(data) {
    this->right = nullptr;
    this->left = nullptr;
}

TransactionNode::TransactionNode(Transaction *data) : tData(data) {
    this->right = nullptr;
    this->left = nullptr;
}

void TransactionNode::Hash() {
    stringstream ss;
    ss << tData.string_dump();
    if (left) ss << left->sHash;
    if (right) ss << right->sHash;
    this->sHash = util::sha256(ss.str());
}
