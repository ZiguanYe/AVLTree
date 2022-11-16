//-----------------------------------------
// You may NOT change anything in this file
//-----------------------------------------
#ifndef INTERNAL_RANGE_H
#define INTERNAL_RANGE_H
#include <stdlib.h>

struct Node {
    int key;
    Node *left, *right, *parent;
    // Constructor for convenience
    Node(int k, Node* lt = nullptr, Node* rt = nullptr, Node* p = nullptr) :
        key(k), left(lt), right(rt), parent(p)
    {}
};

// Prototype
int sumInternalRange(Node * root, int depth, int min, int max);

#endif
