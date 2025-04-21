//
// Created by manta on 4/19/2025.
//

#ifndef BTREE_H
#define BTREE_H
#include "TreeNodes.h"
#include "FileLoader.h"
#include <set>


class BTree {
    TreeNodes* root;
    const int t = 2; //this is the min amount of keys
public:
    BTree();
    ~BTree();
    void BTree_insert(string seq, int id);
    //parent is a nonfull internal node
    //i is index of child from vector if child ptrs
    void split(TreeNodes* parent, int i);
    void insert_nonfull(TreeNodes* node, string seq, int id);

    // set<int> BTree_search(string seq);
    // void BTree_print();
    void load_file(FileLoader& file);
};



#endif //BTREE_H
