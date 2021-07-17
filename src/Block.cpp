//
// Created by chris on 2021-06-25.
//

#include <ctime>
#include <ostream>
#include "Block.h"

Block::Block() {
    tTime_ = time(nullptr);
    transactions = nullptr;
}
Block::Block(const vector<Transaction *> &tx) {
    tTime_ = time(nullptr);
    transactions = new TransactionTree(tx);
    sTxRoot = transactions->root->sHash;
}
Block::Block(const vector<Transaction *> &tx, time_t t) {
    tTime_ = t;
    transactions = new TransactionTree(tx);
    sTxRoot = transactions->root->sHash;
}

void Block::add(Transaction *t) {
    if (transactions == nullptr) transactions = new TransactionTree(t);
    else transactions->add(t);
    sTxRoot = transactions->root->sHash;
}

string Block::getHash() {
    hash();
    return sHash_;
}

json Block::toJson() {
    return {
        {"time",        tTime_},
        {"sPrevHash",   sPrevHash},
        {"stateMerkle", sStateHash},
        {"hash",        hash()},
        {"sTxRoot",     sTxRoot},
        {"tx",          transactions->hashVector()}
    };
}

string Block::hash() {
    stringstream ss;
    ss << tTime_ << sStateHash << sTxRoot;
    for (const string &t : transactions->hashVector()) ss << t;
    ss << sPrevHash;
    return sHash_ = sha256(ss.str());
}

void Block::save() {
    ofstream out("storage/blocks/" + hash() + ".json");
    out << toJson();
    out.close();
}
