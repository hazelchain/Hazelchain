//
// Created by chris on 2021-06-30.
//

#include "Transaction.h"

#include <sstream>

Transaction::Transaction(string  payerIn, string  payeeIn, int64_t amountIn)
        : payer(std::move(payerIn)), payee(std::move(payeeIn)), amount(amountIn) {
}

Transaction::Transaction(Transaction *t)
        : Transaction{ t->payer, t->payee, t->amount } {
}

string Transaction::to_string() const {
    stringstream ss;
    ss << payer << payee << amount;
    return ss.str();
}
