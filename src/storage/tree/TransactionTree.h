//
// Created by chris on 2021-06-30.
//

#ifndef HAZELCHAIN_TRANSACTIONTREE_H
#define HAZELCHAIN_TRANSACTIONTREE_H


#include <iostream>
#include <vector>
#include <fstream>
#include "../../Transaction.h"
#include "TransactionNode.h"
#include <json.hpp>

using namespace std;
using json = nlohmann::json;

struct TransactionTree {
public:
    TransactionNode *root;

    explicit TransactionTree(Transaction *t);

    explicit TransactionTree(const vector<Transaction *> &tx);

    void add(const Transaction &value);

    void add(const Transaction *node);

    void add(TransactionNode *node);

    void print();

    vector<string> hashVector();

private:
    void add(TransactionNode *current, TransactionNode *node);

    void hash();

    string hash(TransactionNode *node);

    vector<string> hashVector(TransactionNode *node);

    void print(TransactionNode *current, int indent, int ia);

    vector<Transaction> getAll(TransactionNode *node);
};


#endif //HAZELCHAIN_TRANSACTIONTREE_H
