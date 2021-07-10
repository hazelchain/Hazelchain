//
// Created by chris on 2021-06-30.
//

#ifndef FLAMECOIN_TRANSACTIONNODE_H
#define FLAMECOIN_TRANSACTIONNODE_H

#include <cstring>
#include <sstream>
#include "../../lib/sha256/sha256.h"
#include "../../Transaction.h"

using namespace std;

class TransactionNode {
public:
    string hash;
    Transaction data;
    TransactionNode *left;
    TransactionNode *right;

    TransactionNode(const Transaction &data);
    TransactionNode(Transaction *data);

    void Hash();
};


#endif //FLAMECOIN_TRANSACTIONNODE_H
