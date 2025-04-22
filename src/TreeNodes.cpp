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

//OLD CODE IN CASE
//citation - https://www.geeksforgeeks.org/insert-operation-in-b-tree///
// void TreeNodes::insert_key(string seq, int id) {
//     if (!is_leaf) {
//         throw runtime_error("insert_key called on internal node, which is incorrect now");
//     }
//
//     if (keys.size() >= 2 * min_degree - 1) {
//         throw runtime_error("Leaf node overflow — should not happen");
//     }
//
//     if (keys.empty()) {
//         keys.push_back({seq, id});
//     } else if (keys.size() == 1) {
//         if (seq < keys[0].first) {
//             keys.insert(keys.begin(), {seq, id});
//         } else {
//             keys.push_back({seq, id});
//         }
//     } else {
//         if (seq < keys[0].first) {
//             keys.insert(keys.begin(), {seq, id});
//         } else if (seq > keys[1].first) {
//             keys.push_back({seq, id});
//         } else {
//             keys.insert(keys.begin() + 1, {seq, id});
//         }
//     }
// }
//
//
//
// void TreeNodes::split_node(int key_index, TreeNodes* child) {
//     // Sanity check: child must be full (3 keys when min_degree is 2)
//     if (child->keys.size() != 2 * min_degree - 1) {
//         cerr << "[ERROR] split_node() called on non-full node. Keys size: " << child->keys.size() << endl;
//         throw runtime_error("Attempting to split a node that is not full.");
//     }
//
//     // Debug info before split
//     cout << "[DEBUG] Splitting child at index " << key_index << ".\n";
//     cout << "         Child keys before split: ";
//     for (const auto& k : child->keys) cout << "\"" << k.first << "\" ";
//     cout << endl;
//
//     // Create a new child node (same leaf status)
//     TreeNodes* new_child = new TreeNodes(child->is_leaf);
//
//     // Transfer second half of keys to new child
//     for (int i = 0; i < min_degree - 1; i++) {
//         new_child->keys.push_back(child->keys[i + min_degree]);
//     }
//
//     // Transfer second half of child pointers if not a leaf
//     if (!child->is_leaf) {
//         for (int i = 0; i < min_degree; i++) {
//             new_child->child_ptr.push_back(child->child_ptr[i + min_degree]);
//         }
//     }
//
//     // Middle key to be pushed up into parent
//     pair<string, int> middle_key = child->keys[min_degree - 1];
//
//     // Resize old child to hold only the first half
//     child->keys.resize(min_degree - 1);
//     if (!child->is_leaf) {
//         child->child_ptr.resize(min_degree);
//     }
//
//     // Insert new child pointer and middle key into parent
//     child_ptr.insert(child_ptr.begin() + key_index + 1, new_child);
//     keys.insert(keys.begin() + key_index, middle_key);
//
//     // Debug info after split
//     cout << "[DEBUG] Middle key \"" << middle_key.first << "\" inserted into parent.\n";
//     cout << "         Parent now has " << keys.size() << " keys and " << child_ptr.size() << " children.\n";
//
//     // Final error checks (hardcoded for min_degree = 2)
//     if (keys.size() > 2) {
//         cerr << "[ERROR] Parent node overflow after split. Keys size: " << keys.size() << endl;
//         throw runtime_error("Parent node exceeds max keys after split");
//     }
//     if (child_ptr.size() > 4) {
//         cerr << "[ERROR] Parent node has too many children after split. child_ptr size: " << child_ptr.size() << endl;
//         throw runtime_error("Parent node exceeds max children after split");
//     }
// }
//
// set<int> TreeNodes::search(string seq) {
//     set<int> result;
//
//     if (keys.empty()) {
//         cout << "[SEARCH] Node is empty. No keys to search." << endl;
//         return result;
//     }
//
//     cout << "[SEARCH] Node keys: ";
//     for (auto& k : keys) {
//         cout << "\"" << k.first << "\" ";
//     }
//     cout << "| Searching for: \"" << seq << "\"" << endl;
//
//     if (keys.size() == 1) {
//         cout << "[COMPARE] Comparing with key: \"" << keys[0].first << "\"" << endl;
//         if (keys[0].first == seq) {
//             cout << "[MATCH] Exact match found at ID: " << keys[0].second << endl;
//             result.insert(keys[0].second);
//         } else if (kmp(seq, keys[0].first)) {
//             cout << "[MATCH] Substring match (KMP) found at ID: " << keys[0].second << endl;
//             result.insert(keys[0].second);
//         }
//
//         if (!is_leaf) {
//             int child_index = (seq < keys[0].first) ? 0 : 1;
//             if (child_index >= child_ptr.size()) {
//                 cout << "[ERROR] Invalid child index " << child_index
//                      << " for node with 1 key. child_ptr size: " << child_ptr.size() << endl;
//                 return result;
//             }
//             cout << "[ROUTE] Going to child[" << child_index << "]" << endl;
//             set<int> c = child_ptr[child_index]->search(seq);
//             result.insert(c.begin(), c.end());
//         }
//     }
//
//     else if (keys.size() == 2) {
//         for (int i = 0; i < 2; i++) {
//             cout << "[COMPARE] Comparing with key: \"" << keys[i].first << "\"" << endl;
//             if (keys[i].first == seq) {
//                 cout << "[MATCH] Exact match found at ID: " << keys[i].second << endl;
//                 result.insert(keys[i].second);
//             } else if (kmp(seq, keys[i].first)) {
//                 cout << "[MATCH] Substring match (KMP) found at ID: " << keys[i].second << endl;
//                 result.insert(keys[i].second);
//             }
//         }
//
//         if (!is_leaf) {
//             int child_index;
//             if (seq < keys[0].first) {
//                 child_index = 0;
//             } else if (seq < keys[1].first) {
//                 child_index = 1;
//             } else {
//                 child_index = 2;
//             }
//
//             if (child_index >= child_ptr.size()) {
//                 cout << "[ERROR] Invalid child index " << child_index
//                      << " for node with 2 keys. child_ptr size: " << child_ptr.size() << endl;
//                 return result;
//             }
//
//             cout << "[ROUTE] Going to child[" << child_index << "]" << endl;
//             set<int> c = child_ptr[child_index]->search(seq);
//             result.insert(c.begin(), c.end());
//         }
//     }
//
//     return result;
// }
//
//
// void TreeNodes::print() {
//     for (int i = 0; i < keys.size(); i++) {
//         cout << "Sequence: "<< keys[i].first << ". ID: " << keys[i].second << endl;
//     }
//     if (is_leaf == false) {
//         for (int i = 0; i < child_ptr.size(); i++) {
//             child_ptr[i]->print();
//         }
//     }
// }
// int TreeNodes::get_key_size() {
//     return keys.size();
// }
// void TreeNodes::set_ptr(TreeNodes* child) {
//     child_ptr.push_back(child);
// }
// TreeNodes *TreeNodes::get_child(int i) {
//     if (i >= 0 && i < child_ptr.size()) return child_ptr[i];
//     throw out_of_range("Invalid child index");
// }
// pair<string, int> TreeNodes::get_key(int i) {
//     if (i >= 0 && i < keys.size()) return keys[i];
//     throw out_of_range("Invalid key index");
// }
//
// int TreeNodes::get_min_degree() {
//     return min_degree;
// }
//
// bool TreeNodes::getleaf() {
//     return is_leaf;
// }
// int TreeNodes::get_child_index(const string& seq) const {
//     if (keys.size() == 1) return (seq < keys[0].first) ? 0 : 1;
//     if (seq < keys[0].first) return 0;
//     if (seq < keys[1].first) return 1;
//     return 2;
// }
// void TreeNodes::insert_into_leaf(const string& seq, int id) {
//     if (keys.empty() || seq < keys[0].first) keys.insert(keys.begin(), {seq, id});
//     else if (keys.size() == 1 || seq > keys[1].first) keys.push_back({seq, id});
//     else keys.insert(keys.begin() + 1, {seq, id});
// }