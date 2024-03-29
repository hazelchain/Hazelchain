//
// Created by chris on 2021-06-30.
//

#include "TransactionTree.h"
#include "../../util/util.h"
#include "../../util/sha256.h"

TransactionTree::TransactionTree(Transaction *t) {
    root = new TransactionNode(t);
    _hash();
}

TransactionTree::TransactionTree(const std::vector<Transaction> &tx) {
    root = new TransactionNode(tx.at(0));

    for (int i = 1; i < tx.size(); ++i) {
        add(tx.at(i));
    }
    _hash();
}

TransactionTree::TransactionTree(std::initializer_list<Transaction> tx) {
    for (auto i = tx.begin(); i != tx.end(); ++i) {
        if (i == tx.begin()) {
            root = new TransactionNode(i);
            return;
        }
        _add(root, new TransactionNode(i));
    }
    _hash();
}

void TransactionTree::add(const Transaction &value) {
    _add(root, new TransactionNode(value));
}

void TransactionTree::add(const Transaction *node) {
    _add(root, new TransactionNode(node));
    _hash();
}

void TransactionTree::_add(TransactionNode *current, TransactionNode *node) {
    node->Hash();
    if (util::isGreaterThan(node->sHash, current->sHash)) {
        if (current->left != nullptr) _add(current->left, node);
        else current->left = node;
    } else {
        if (current->right != nullptr) _add(current->right, node);
        else current->right = node;
    }
}

void TransactionTree::_hash() {
    _hash(root);
}

std::string TransactionTree::_hash(TransactionNode *node) {
    std::stringstream ss;
    ss << node->tData.dump();
    if (node->left) ss << _hash(node->left);
    if (node->right) ss << _hash(node->right);
    node->sHash = util::sha256(ss.str());
    return node->sHash;
}

std::vector<std::string> TransactionTree::hashVector() {
    return _hashVector(root);
}

std::vector<std::string> TransactionTree::_hashVector(TransactionNode *node) {
    std::vector<std::string> out;
    out.push_back(node->sHash);
    if (node->left) {
        std::vector<std::string> l = _hashVector(node->left);
        out.insert(out.end(), l.begin(), l.end());
    }
    if (node->right) {
        std::vector<std::string> l = _hashVector(node->right);
        out.insert(out.end(), l.begin(), l.end());
    }
    return out;
}
