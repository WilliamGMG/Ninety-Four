//
// Created by manta on 4/19/2025.
//

#include "TreeNodes.h"

#include <iostream>

TreeNodes::TreeNodes(bool is_leaf = false) {
    this->is_leaf = is_leaf;
}
TreeNodes::~TreeNodes() {
    for (int i = 0; i < this->child_ptr.size(); i++) {
        delete this->child_ptr[i];
    }
}
vector<TreeNodes *> TreeNodes::get_child_ptrs() {
    return child_ptr;
}
bool TreeNodes::get_is_leaf() {
    return is_leaf;
}
TreeNodes *TreeNodes::get_a_child(int i) {
    return child_ptr[i];
}
int TreeNodes::get_key_count() {
    return keys.size();
}
void TreeNodes::add_child(TreeNodes *node, int i) {
    child_ptr.insert(child_ptr.begin() + i, node);
}
void TreeNodes::add_keys_m(pair<string, int> newkey) {
    keys.push_back(newkey);

    for (int i = keys.size() - 2; i >= 0; i--) {
        if (keys[i].first > newkey.first) {
            keys[i+1] = keys[i];
            keys[i] = newkey;
            return;
        }
    }
    keys[keys.size()-1] = newkey;
}
pair<string, int> TreeNodes::get_key(int i) {
    return keys[i];
}
void TreeNodes::add_keys(pair<string, int> newkey) {
    keys.push_back(newkey);
}
void TreeNodes::resize_key( int index) {
    keys.resize(index);
}
 void TreeNodes::resize_child(int i) {
     child_ptr.resize(i);
 }
int TreeNodes::get_child_count() {
    return child_ptr.size();
}

vector<pair<string, int>> TreeNodes::get_keys() {
    return keys;
}

//Citation: https://www.youtube.com/watch?v=GTJr8OvyEVQ, https://www.youtube.com/watch?v=V5-7GzOfADQ
vector<int> TreeNodes::lps(string seq) {
     vector<int> lps(seq.size(), 0);
     int len = 0;
     int i = 1;

     while (i < seq.size()) {
         if (seq[i] == seq[len]) {
             len++;
             lps[i] = len;
             i++;
         }
         else {
             if (len != 0) {
                 len = lps[len-1];
             }
             else {
                 lps[i++] = 0;
             }
         }
     }
     return lps;
 }

bool TreeNodes::kmp(string seq, string data) {
    if (seq.empty()) {
        return false;
    }
    if (data.empty()) {
        return false;
    }
    vector<int> x = lps(seq);
    int i = 0, j = 0;

    while (i < data.size()) {
     if (data[i] == seq[j]) {
         i++;
         j++;
         if (j == seq.size()) {
             return true;
         }
     } else {
         if (j != 0) {
             j = x[j-1];
         }
         else {
             i++;
         }
     }
    }
    return false;
}
