//
// Created by manta on 4/19/2025.
//

#ifndef BTREE_H
#define BTREE_H
#include "TreeNodes.h"
#include "FileLoader.h"


class BTree {
    TreeNodes* root;
public:
    BTree();
    BTree(FileLoader& fileLoader);
    ~BTree();
    void BTree_insert(string seq, int id);
    set<int> BTree_search(string seq);
    void BTree_print();
    void load_file(FileLoader& file);

    set<int> BTree_BFS_search(string seq);
};



#endif //BTREE_H
