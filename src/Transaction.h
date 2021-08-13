//
// Created by chris on 2021-06-30.
//

#ifndef HAZELCHAIN_TRANSACTION_H
#define HAZELCHAIN_TRANSACTION_H

#include <cstdint>
#include <string>
#include <vector>

class Transaction {
public:
    Transaction(std::string payerIn, std::string payeeIn, int64_t amountIn);

    explicit Transaction(Transaction *t);

    explicit Transaction(const Transaction *t);

    std::string payer;
    std::string payee;
    int64_t amount;

    [[nodiscard]] std::string dump() const;

};


#endif //HAZELCHAIN_TRANSACTION_H
