//
// Created by chris on 2021-06-30.
//

#ifndef HAZELCHAIN_TRANSACTIONTREE_H
#define HAZELCHAIN_TRANSACTIONTREE_H

#include <vector>
#include <fstream>
#include "../../Transaction.h"
#include "TransactionNode.h"

struct TransactionTree {
public:
    TransactionNode *root;

    explicit TransactionTree(Transaction *t);

    explicit TransactionTree(const std::vector<Transaction> &tx);

    TransactionTree(std::initializer_list<Transaction> tx);

    void add(const Transaction &value);

    void add(const Transaction *node);

    void print();

    std::vector<std::string> hashVector();

private:
    void _add(TransactionNode *current, TransactionNode *node);

    void _hash();

    std::string _hash(TransactionNode *node);

    std::vector<std::string> _hashVector(TransactionNode *node);

    void _print(TransactionNode *current, int indent, int ia);
};


#endif //HAZELCHAIN_TRANSACTIONTREE_H
