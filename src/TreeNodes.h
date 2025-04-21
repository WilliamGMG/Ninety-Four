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
    vector<TreeNodes*> get_child_prts();
    TreeNodes* get_a_child(int i);
    bool get_is_leaf();
    int get_key_count();
    void add_child(TreeNodes* child, int i);
    void add_keys_m(pair<string, int> newkey);
    void add_keys(pair<string, int> newkey);
    void resize_key(int index);
    pair<string, int> get_key(int i);
    void resize_child(int i);
    int get_child_count();


    // void insert_key(string seq, int id);
    // void split_node(int key_index, TreeNodes* child);
    // set<int> search(string seq);
    // void print();
    // int get_key_size();
    // void set_ptr(TreeNodes* child);
    // bool kmp(string seq, string data);
    // vector<int> lps(string seq);
    // int get_min_degree();
    // bool getleaf();
    // pair<string,int> get_key(int i);
    // TreeNodes* get_child(int i);
    // int get_child_index(const string& seq) const;
    // void insert_into_leaf(const string& seq, int id);




};



#endif //TREENODES_H
