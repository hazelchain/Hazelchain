//
// Created by chris on 2021-06-30.
//

#ifndef HAZELCHAIN_TRANSACTION_H
#define HAZELCHAIN_TRANSACTION_H

#include <cstdint>
#include <string>
#include <vector>

using namespace std;

class Transaction {
public:
    Transaction(string payerIn, string payeeIn, int64_t amountIn);

    explicit Transaction(Transaction *t);

    explicit Transaction(const Transaction *t);

    string payer;
    string payee;
    int64_t amount;

    string string_dump() const;

};


#endif //HAZELCHAIN_TRANSACTION_H
