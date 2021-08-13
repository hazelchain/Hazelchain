//
// Created by chris on 2021-06-25.
//

#ifndef HAZELCHAIN_BLOCK_H
#define HAZELCHAIN_BLOCK_H

#include <cstring>
#include <json.hpp>
#include "storage/tree/TransactionTree.h"

using json = nlohmann::json;

class Block {
public:
    std::string sPrevHash;
    std::string sStateHash;
    std::string sTxRoot;
    TransactionTree *transactions;

    Block();

    Block(std::initializer_list<Transaction> tx, time_t t);

    std::string getHash();

    json toJson();

    void add(Transaction *t);

    void save();

private:
    std::string sHash_;
    time_t tTime_;

    std::string hash();

};


#endif //HAZELCHAIN_BLOCK_H
