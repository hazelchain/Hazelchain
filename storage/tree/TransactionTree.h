//
// Created by chris on 2021-06-30.
//

#ifndef FLAMECOIN_TRANSACTIONTREE_H
#define FLAMECOIN_TRANSACTIONTREE_H


#include <iostream>
#include <vector>
#include <fstream>
#include "../../Transaction.h"
#include "Node.h"
#include "TransactionNode.h"
#include "../../lib/json/json.hpp"

using namespace std;
using json = nlohmann::json;

struct TransactionTree {
public:
    TransactionNode *root;

    explicit TransactionTree(TransactionNode *node);
    explicit TransactionTree(Transaction *t);
    explicit TransactionTree(vector<Transaction> tx);

    void add(const Transaction &value);
    void add(Transaction *node);
    void add(TransactionNode *node);

    vector<Transaction> getAll();

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


#endif //FLAMECOIN_TRANSACTIONTREE_H
