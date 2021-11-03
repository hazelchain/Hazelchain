//
// Created by chris on 2021-06-25.
//

#include "Block.h"
#include "util/sha256.h"
#include <ctime>
#include <sstream>

Block::Block() {
    tTime_ = time(nullptr);
    transactions = nullptr;
}

Block::Block(std::initializer_list<Transaction> tx, time_t t) {
    tTime_ = t;
    transactions = new TransactionTree(tx);
    sTxRoot = transactions->root->sHash;
}

void Block::add(Transaction *t) {
    if (transactions == nullptr) transactions = new TransactionTree(t);
    else transactions->add(t);
    sTxRoot = transactions->root->sHash;
}

std::string Block::getHash() {
    hash();
    return sHash_;
}

json Block::toJson() {
    return {
            {"time",        tTime_},
            {"sPrevHash",   sPrevHash},
            {"stateMerkle", sStateHash},
            {"_hash",        hash()},
            {"sTxRoot",     sTxRoot},
            {"tx",          transactions->hashVector()}
    };
}

std::string Block::hash() {
    std::stringstream ss;
    ss << tTime_ << sStateHash << sTxRoot;
    for (const std::string &t : transactions->hashVector()) ss << t;
    ss << sPrevHash;
//    return sHash_ = util::sha256(ss.str());
    return "no";
}

void Block::save() {
    std::ofstream out("storage/blocks/" + hash() + ".json");
    out << toJson();
    out.close();
}
