//
// Created by chris on 2021-06-28.
//

#ifndef FLAMECOIN_TREE_H
#define FLAMECOIN_TREE_H

#include <cstring>
#include <vector>
#include <fstream>
#include "Node.h"

using namespace std;

template<class T>
struct Tree {
public:
    Node<T> *root;

    explicit Tree(Node<T> *node) {
        node->left = nullptr;
        node->right = nullptr;
        root = node;
    }
    explicit Tree(T data)
            : Tree{ new Node<T>(data) } {
    }

    void add(T value) {
        add(new Node<T>(value));
    }
    void add(Node<T> *node) {
        add(root, node, 0);
        Hash();
    }

    void print() {
        print(root, 0, 4);
    }

    void save(const string& filename) {
        stringstream ss;
        ss << save(root, 0, 2);
        ofstream of(filename + ".tree");
        of << ss.str();
        of.close();
    }

    void Hash() {
        Hash(root);
    }

private:
    void add(Node<T> *current, Node<T> *node, int index) {
        if (current->hash[index] < node->hash[index]) {
            if (current->left) add(current->left, node, index + 1);
            else current->left = node;
        } else {
            if (current->right) add(current->right, node, index + 1);
            else current->right = node;
        }
    }

    void print(Node<T> *node, int indent, int ia) {
        stringstream p;
        for (int i = 0; i < indent; ++i) p << ' ';
        cout << p.str() << node->hash << endl;


        if (node->left) print(node->left, indent + ia, ia);
        if (node->right) print(node->right, indent + ia, ia);
    }

    string save(Node<T> *node, int indent, int ia) {
        stringstream spaces;
        for (int i = 0; i < indent; ++i) spaces << ' ';

        stringstream ss;
        ss << spaces.str() << node->hash << endl;

        if (node->left) ss << save(node->left, indent + ia, ia);
        if (node->right) ss << save(node->right, indent + ia, ia);
        return ss.str();
    }

    void Hash(Node<T> *node) {
        if (node->left) Hash(node->left);
        if (node->right) Hash(node->right);
        node->Hash();
    }
};

#endif //FLAMECOIN_TREE_H
