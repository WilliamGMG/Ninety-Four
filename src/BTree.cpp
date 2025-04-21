//
// Created by manta on 4/19/2025.
//

#include "BTree.h"

#include <iostream>

BTree::BTree() {
    root = new TreeNodes(true);
}
BTree::~BTree() {
    delete root;
}

void BTree::BTree_insert(string seq, int id) {
    if (root->get_key_count() == 2 *t -1) {
        TreeNodes* temp = root;
        TreeNodes *new_node = new TreeNodes(false);
        root = new_node;
        new_node->add_child(temp,0);
        split(new_node,0);
        insert_nonfull(new_node, seq, id);
    }
    else {
        insert_nonfull(root, seq, id);
    }
}
//should be a non full parent nodes and index i of child that is full
void BTree::split(TreeNodes* parent, int i) {
    TreeNodes* full_child = parent->get_a_child(i);

    if (full_child->get_key_count() != 2 * t - 1) {
        throw runtime_error("[ERROR] Attempted to split non-full child. Key count mismatch.");
    }

    if (parent->get_key_count() >= 2 * t - 1) {
        throw runtime_error("[ERROR] Parent node overflow after split. Too many keys.");
    }

    TreeNodes* x = new TreeNodes(full_child->get_is_leaf());

    parent->add_keys_m(full_child->get_key(t - 1));
    parent->add_child(x, i + 1);

    for (int j = 0; j < t - 1; j++) {
        x->add_keys(full_child->get_key(t + j));
    }

    full_child->resize_key(t - 1);

    if (!full_child->get_is_leaf()) {
        for (int j = 0; j < t; j++) {
            x->add_child(full_child->get_a_child(t + j), j);
        }
        full_child->resize_child(t);
    }
}

void BTree::insert_nonfull(TreeNodes *node, string seq, int id) {
    //if leaf insert it//
    if (node->get_is_leaf() == true) {
        node->add_keys_m(pair<string, int>(seq, id));
    }
    //if not leaf, must find child
    else {
        //while keys size is greater than 0, and seq < node key at 1
        // keeping track of index because that is the the child index
        // find child index, see if it is full, split, decide which child to go into, recurse into the child//

        int k = node->get_key_count()-1;
        while (k >= 0) {
            if (seq < node->get_key(k).first) {
                k--;
            }
            else {
                break;
            }
        }
        k++;
        TreeNodes *temp = node->get_a_child(k);
        if (temp->get_key_count() == 2*t -1) {
            split(node,k);
            int i = node->get_key_count() -1;
            while (i >= 0) {
                if (seq < node->get_key(i).first) {
                    i--;
                }
                else {
                    break;
                }
            }
            i++;
            temp = node->get_a_child(i);
        }
        insert_nonfull(temp, seq, id);

    //     for (int i = node->get_child_count(); i >= 0; i++) {
    //         if (temp->get_key(i) > seq) {
    //             TreeNodes *temp = node->get_a_child(i);
    //             index++;
    //             break;
    //         }
    //     }
    //     if (temp->get_key_count() == 2*t -2) {
    //         split(root, index)
    //         int index = 0;
    //         for (int i = node->get_child_count(); i >= 0; i++) {
    //             if (temp->get_key(i) > seq) {
    //                 TreeNodes *temp = node->get_a_child(i);
    //                 index++;
    //                 break;
    //     }
    //
    }
}




// set<int> BTree::BTree_search(string seq) {
//     set<int> result=root->search(seq);
//     if (result.empty()) {
//         cout << "Sequence not found" << endl;
//     }
//     return result;
// }
//
// void BTree::BTree_print() {
//     root->print();
// }
void BTree::load_file(FileLoader& file) {
    vector<pair<int, string>> chunk;

    while (true) {
        chunk.clear();  // Clear to avoid appending to old data
        LoadChunkStatus status = file.loadChunk(chunk);

        for (const auto& [id, seq] : chunk) {
            if (!seq.empty()) {
                BTree_insert(seq, id);
            }
        }

        if (status == LoadChunkStatus::EndOfFile) {
            break;
        } else if (status == LoadChunkStatus::FailedToOpenFile) {
            cerr << "[ERROR] FileLoader encountered an error while loading chunk." << endl;
            break;
        }
    }
}

