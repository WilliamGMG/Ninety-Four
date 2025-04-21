//
// Created by manta on 4/19/2025.
//

#include "TreeNodes.h"

#include <iostream>

TreeNodes::TreeNodes(bool is_leaf) {
    this->min_degree = 2;
    this->is_leaf = is_leaf;
}
TreeNodes::~TreeNodes() {
    for (int i = 0; i < this->child_ptr.size(); i++) {
        delete this->child_ptr[i];
    }
}
//citation - https://www.geeksforgeeks.org/insert-operation-in-b-tree///
void TreeNodes::insert_key(string seq, int id) {
    if (is_leaf ==true) {
        if (keys.empty()) {
            keys.push_back({seq, id});
        }
        else if (keys.size() == 1) {
            if (seq < keys[0].first) {
                keys.insert(keys.begin(),{seq, id});
            }
            else {
                keys.push_back({seq, id});
            }
        }
        else {
            if (seq < keys[0].first) {
                keys.insert(keys.begin(),{seq, id});
            }
            else if (seq > keys[1].first) {
                keys.push_back({seq, id});
            }
            else {
                keys.insert(keys.begin() + 1, {seq, id});
            }
        }
        return;
    }

    int child_index;
    if (keys.size() == 1) {
        if (seq < keys[0].first) {
            child_index = 0;
        }
        else {
            child_index = 1;
        }
    }
    else if (keys.size() == 2) {
        if (seq < keys[0].first) {
            child_index = 0;
        }
        else if (seq < keys[1].first) {
            child_index = 1;
        }
        else {
            child_index = 2;
        }
    }
    if (child_ptr[child_index] -> keys.size() == 2*min_degree -1) {
        split_node(child_index, child_ptr[child_index]);
        if (seq > keys[child_index].first) {
            child_index++;
        }
    }
    child_ptr[child_index]->insert_key(seq, id);
}

//citation - https://www.geeksforgeeks.org/insert-operation-in-b-tree/
void TreeNodes::split_node(int key_index, TreeNodes* child) {
    TreeNodes* new_child = new TreeNodes(child->is_leaf);
    for (int i = 0; i < min_degree - 1; i++) {
        new_child->keys.push_back(child->keys[i + min_degree]);
    }
    if (child->is_leaf == false) {
        for (int i = 0; i < min_degree; i++) {
            new_child->child_ptr.push_back(child->child_ptr[i+ min_degree]);
        }
    }
    pair<string, int> middle_key = child->keys[min_degree-1];

    child->keys.resize(min_degree-1);
    if (child->is_leaf == false) {
        child->child_ptr.resize(min_degree);
    }
    child_ptr.insert(child_ptr.begin() + key_index +1, new_child);
    keys.insert(keys.begin() +key_index, middle_key);
}
set<int> TreeNodes::search(string seq) {
    set<int> result;
    if (keys.empty()) {
        return result;
    }
    else if (keys.size() == 1) {
        if (keys[0].first == seq) {
            result.insert(keys[0].second);
        }
        else if (kmp(seq,keys[0].first) == true) {
            result.insert(keys[0].second);
        }

        if (is_leaf == false) {
            if (seq < keys[0].first) {
                set<int> c = child_ptr[0]->search(seq);
                result.insert(c.begin(), c.end());
            }
            else {
                set<int> c = child_ptr[1]->search(seq);
                result.insert(c.begin(), c.end());
            }
        }
    }
    else if (keys.size() == 2) {
        if (keys[0].first == seq) {
            result.insert(keys[0].second);
        }
        else if (kmp(seq,keys[0].first) == true) {
            result.insert(keys[0].second);
        }
        if (keys[1].first == seq) {
            result.insert(keys[1].second);
        }
        else if (kmp(seq,keys[1].first) == true) {
            result.insert(keys[1].second);
        }

        if (is_leaf == false) {
            if (seq < keys[0].first) {
                set<int> c = child_ptr[0]->search(seq);
                result.insert(c.begin(), c.end());
            }
            else if (seq < keys[1].first) {
                set<int> c = child_ptr[1]->search(seq);
                result.insert(c.begin(), c.end());
            }
            else {
                set<int> c = child_ptr[2]->search(seq);
                result.insert(c.begin(), c.end());
            }
        }

    }
    return result;
}

void TreeNodes::print() {
    for (int i = 0; i < keys.size(); i++) {
        cout << "Sequence: "<< keys[i].first << ". ID: " << keys[i].second << endl;
    }
    if (is_leaf == false) {
        for (int i = 0; i < child_ptr.size(); i++) {
            child_ptr[i]->print();
        }
    }
}
int TreeNodes::get_key_size() {
    return keys.size();
}
void TreeNodes::set_ptr(TreeNodes* child) {
    child_ptr.push_back(child);
}
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

//Citation: Level Order Traversal from Sum of Right Leaves (in Module 3 Slides)
set<int> TreeNodes::BFS_search(string seq) {
    set<int> result;
    //Edge Case
    if (keys.empty() || seq.empty()){
        return {};
    }

    queue<TreeNodes*> q;
    q.push(this); //TreeNode self call

    while (!q.empty()){
        TreeNodes* currNode = q.front();

        //Check the keys in the current TreeNode
        for (auto & key : currNode->keys){
            //Search Function: key direct match || subsequence check
            if (key.first == seq || currNode->kmp(seq,key.first)){
                result.insert(key.second);
            }
        }

        //Push in the Children after Level Done
        if (!currNode->is_leaf){
            for (TreeNodes* child:currNode->child_ptr){
                q.push(child);
            }
        }

        q.pop();
    }

    return result;
}


