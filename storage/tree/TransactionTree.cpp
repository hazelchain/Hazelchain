//
// Created by chris on 2021-06-30.
//

#include "TransactionTree.h"
#include "../../util.h"

TransactionTree::TransactionTree(TransactionNode *node) {
    root = node;
    hash();
}
TransactionTree::TransactionTree(Transaction *t) {
    root = new TransactionNode(t);
    hash();
}
TransactionTree::TransactionTree(vector<Transaction> tx) {
    root = new TransactionNode(tx.at(0));

    for (int i = 1; i < tx.size(); ++i) {
        add(tx.at(i));
    }
    hash();
}


void TransactionTree::add(const Transaction &value) {
    add(root, new TransactionNode(value));
    hash();
}
void TransactionTree::add(Transaction *node) {

}
void TransactionTree::add(TransactionNode *node) {
    add(root, node);
}
void TransactionTree::add(TransactionNode *current, TransactionNode *node) {
    node->Hash();
    if(util::isGreaterThan(node->hash, current->hash)) {
        if (current->left != nullptr) add(current->left, node);
        else current->left = node;
    }
    else {
        if (current->right != nullptr) add(current->right, node);
        else current->right = node;
    }
}
void TransactionTree::print() {
    print(root, 0, 4);
}

void TransactionTree::print(TransactionNode *current, int indent, int ia) {
    cout << util::string_of(' ', indent) << current->hash << endl;

    if (current->left) print(current->left, indent + ia, ia);
    if (current->right) print(current->right, indent + ia, ia);
}
void TransactionTree::hash() {
    hash(root);
}

string TransactionTree::hash(TransactionNode *node) {
    stringstream ss;
    ss << node->data.to_string();
    if (node->left) ss << hash(node->left);
    if (node->right) ss << hash(node->right);
    node->hash = sha256(ss.str());
    return node->hash;
}

vector<string> TransactionTree::hashVector() {
    return hashVector(root);
}

vector<string> TransactionTree::hashVector(TransactionNode *node) {
    vector<string> out;
    out.push_back(node->hash);
    if (node->left) {
        vector<string> l = hashVector(node->left);
        out.insert(out.end(), l.begin(), l.end());
    }
    if (node->right) {
        vector<string> l = hashVector(node->right);
        out.insert(out.end(), l.begin(), l.end());
    }
    return out;
}

vector<Transaction> TransactionTree::getAll() {
    return getAll(root);
}

vector<Transaction> TransactionTree::getAll(TransactionNode *node) {
    vector<Transaction> out;
    out.push_back(node->data);
    if (node->left) {
        vector<Transaction> p = getAll(node->left);
        out.insert(out.end(), p.begin(), p.end());
    }
    if (node->right) {
        vector<Transaction> p = getAll(node->right);
        out.insert(out.end(), p.begin(), p.end());
    }
    return out;
}
