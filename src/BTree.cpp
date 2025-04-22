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
    }
}

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

//Citation: Level Order Traversal from Sum of Right Leaves (in Module 3 Slides)
//Private Search Call
set<int> BTree::BTree_BFSsearch(string seq){
    set<int> result;
    //Edge Case
    if (root == nullptr || seq.empty()){
        return {};
    }

    queue<TreeNodes*> q;
    q.push(root); //Add first Node

    while (!q.empty()){
        TreeNodes* currNode = q.front();

        //Check the keys in the current TreeNode
        for (auto & key : currNode->get_keys()){
            //Search Function: key direct match || subsequence check
            if (key.first == seq || currNode->kmp(seq,key.first)){
                result.insert(key.second);
            }
        }

        //Push in the Children ~Equivalent to Left and Right Child Push in BST
        if (!currNode->get_is_leaf()){
            for (auto child : currNode->get_child_ptrs()){
                q.push(child);
            }
        }

        q.pop();
    }

    return result;
}

//Public Search Call
set<int> BTree::search(string seq) {
    return BTree_BFSsearch(seq);
}
