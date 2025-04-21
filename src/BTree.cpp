//
// Created by manta on 4/19/2025.
//

#include "BTree.h"

#include <iostream>

BTree::BTree() {
    root = new TreeNodes(true);
}
BTree::BTree(FileLoader& fileLoader) {
    root = new TreeNodes(true);
    load_file(fileLoader);
}
BTree::~BTree() {
    delete root;
}

void BTree::BTree_insert(string seq, int id) {
    if (root->get_key_size() == 3) {
        TreeNodes* new_node = new TreeNodes(false);
        new_node->set_ptr(root);
        new_node->split_node(0,root);
        root = new_node;
    }
    root->insert_key(seq, id);
}

set<int> BTree::BTree_search(string seq) {
    set<int> result=root->search(seq);
    return result;
}

void BTree::BTree_print() {
    root->print();
}
void BTree::load_file(FileLoader& file) {
    vector<pair<int, string>> chunk;
    while (file.loadChunk(chunk) != LoadChunkStatus::EndOfFile) {
        for (const auto& [id,seq] : chunk) {
            BTree_insert(seq,id);
        }
    }
}

set<int> BTree::BTree_BFS_search(string seq) {
    return root->BFS_search(seq);
}
