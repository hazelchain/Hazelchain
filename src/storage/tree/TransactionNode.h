//
// Created by chris on 2021-06-30.
//

#ifndef HAZELCHAIN_TRANSACTIONNODE_H
#define HAZELCHAIN_TRANSACTIONNODE_H

#include <cstring>
#include <sstream>
#include "../../libs/sha256/sha256.h"
#include "../../Transaction.h"

using namespace std;

class TransactionNode {
public:
    string sHash;
    Transaction tData;
    TransactionNode *left;
    TransactionNode *right;

    explicit TransactionNode(Transaction data);
    explicit TransactionNode(const Transaction *data);
    explicit TransactionNode(Transaction *data);

    void Hash();
};


#endif //HAZELCHAIN_TRANSACTIONNODE_H
