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
    int min_degree;
    bool is_leaf;

    public:
    TreeNodes(bool is_leaf);
    ~TreeNodes();
    void insert_key(string seq, int id);
    void split_node(int key_index, TreeNodes* child);
    set<int> search(string seq);
    void print();
    int get_key_size();
    void set_ptr(TreeNodes* child);

};



#endif //TREENODES_H
