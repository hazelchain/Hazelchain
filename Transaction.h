//
// Created by chris on 2021-06-30.
//

#ifndef FLAMECOIN_TRANSACTION_H
#define FLAMECOIN_TRANSACTION_H

#include <cstdint>
#include <string>
#include <vector>
using namespace std;

class Transaction {
public:
    Transaction(string payerIn, string payeeIn, int64_t amountIn);
    explicit Transaction(Transaction *t);

    string payer;
    string payee;
    int64_t amount;

    string to_string() const;

};


#endif //FLAMECOIN_TRANSACTION_H
