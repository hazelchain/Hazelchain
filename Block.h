//
// Created by chris on 2021-06-25.
//

#ifndef HAZELCHAIN_BLOCK_H
#define HAZELCHAIN_BLOCK_H

#include <cstring>
#include "storage/tree/TransactionTree.h"
#include "libs/json/json.hpp"

using namespace std;
using json = nlohmann::json;

class Block {
public:
    string sPrevHash;
    string sStateHash;
    string sTxRoot;
    TransactionTree *transactions;

    Block();
    explicit Block(const vector<Transaction *> &tx);

    string getHash();
    json toJson();
    void add(Transaction *t);
    void save();

private:
    string sHash_;
    time_t tTime_;

    string hash();

};


#endif //HAZELCHAIN_BLOCK_H
