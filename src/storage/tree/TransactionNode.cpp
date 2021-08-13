//
// Created by chris on 2021-06-30.
//

#include <sstream>
#include "TransactionNode.h"
#include "../../util/sha256.h"

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
    std::stringstream ss;
    ss << tData.dump();
    if (left) ss << left->sHash;
    if (right) ss << right->sHash;
    this->sHash = util::sha256(ss.str());
}
