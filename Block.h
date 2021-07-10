//
// Created by chris on 2021-06-25.
//

#ifndef FLAMECOIN_BLOCK_H
#define FLAMECOIN_BLOCK_H

#include <cstring>
#include "storage/tree/TransactionTree.h"
#include "lib/json/json.hpp"

using namespace std;
using json = nlohmann::json;

class Block {
public:
    string prevHash;
    string stateHash;
    string txRoot;
    TransactionTree *transactions;

    Block();
    explicit Block(Transaction *tx);
    explicit Block(vector<Transaction> tx);
    explicit Block(TransactionTree tx);

    string getHash();
    json toJson();
    void add(Transaction *t);
    void save();

private:
    string hash_;
    time_t time_;

    string hash();

};


#endif //FLAMECOIN_BLOCK_H
