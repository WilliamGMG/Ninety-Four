//
// Created by manta on 4/19/2025.
//

#ifndef TREENODES_H
#define TREENODES_H


#include <vector>
#include <string>
#include <set>

using namespace std;

class TreeNodes {
    vector<TreeNodes*> child_ptr;
    vector<pair<string, int>> keys;
    bool is_leaf;

public:
    TreeNodes(bool is_leaf);
    ~TreeNodes();

    vector<TreeNodes*> get_child_ptrs();
    TreeNodes* get_a_child(int i);
    bool get_is_leaf();
    int get_key_count();
    int get_child_count();
    vector<pair<string,int>> get_keys();

    void add_child(TreeNodes *child, int i);
    void add_keys_m(pair<string, int> newkey);
    void add_keys(pair<string, int> newkey);

    void resize_key(int index);
    pair<string, int> get_key(int i);
    void resize_child(int i);

    bool kmp(string seq, string data);
    vector<int> lps(string seq);
};



#endif //TREENODES_H
