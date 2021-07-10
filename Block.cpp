//
// Created by chris on 2021-06-25.
//

#include <ctime>
#include <ostream>
#include "Block.h"

Block::Block() {
    time_ = time(nullptr);
    transactions = nullptr;
}
Block::Block(Transaction *tx) {
    time_ = time(nullptr);
    transactions = new TransactionTree(tx);
    txRoot = transactions->root->hash;
}
Block::Block(vector<Transaction> tx) {
    time_ = time(nullptr);
    transactions = new TransactionTree(std::move(tx));
    txRoot = transactions->root->hash;
}
Block::Block(TransactionTree tx) {
    time_ = time(nullptr);
    transactions = new TransactionTree(tx.root);
    for (const Transaction& t : tx.getAll()) {
        transactions->add(t);
    }
    txRoot = transactions->root->hash;
}

void Block::add(Transaction *t) {
    if (transactions == nullptr) transactions = new TransactionTree(t);
    else transactions->add(t);
    txRoot = transactions->root->hash;
}

string Block::getHash() {
    if (hash_.empty()) hash();
    return hash_;
}

json Block::toJson() {
    return {
        {"time", time_},
        {"prevHash", prevHash},
        {"stateMerkle", stateHash},
        {"hash", hash()},
        {"txRoot", txRoot},
        {"tx", transactions->hashVector()}
    };
}

string Block::hash() {
    stringstream ss;
    ss << time_ << stateHash << txRoot;
    for (const string &t : transactions->hashVector()) ss << t;
    ss << prevHash;
    return hash_ = sha256(ss.str());
}

void Block::save() {
    ofstream out("storage/blocks/" + hash() + ".json");
    out << toJson();
    out.close();
}
