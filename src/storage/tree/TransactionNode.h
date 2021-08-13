//
// Created by chris on 2021-06-30.
//

#ifndef HAZELCHAIN_TRANSACTIONNODE_H
#define HAZELCHAIN_TRANSACTIONNODE_H

#include <string>
#include "../../Transaction.h"

class TransactionNode {
public:
    std::string sHash;
    Transaction tData;
    TransactionNode *left;
    TransactionNode *right;

    explicit TransactionNode(Transaction data);

    explicit TransactionNode(const Transaction *data);

    explicit TransactionNode(Transaction *data);

    void Hash();
};


#endif //HAZELCHAIN_TRANSACTIONNODE_H
