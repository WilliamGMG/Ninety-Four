#include <iostream>
#include <string>
#include <vector>
#include "BTree.h"

using namespace std;

int main() {
    // Create B-tree with a chosen minimum degree (e.g., 2)
    BTree btree;

    // Insert a range of sequences into the B-tree
    cout << "[DEBUG] Inserting test sequences from ID 0 to 50009..." << endl;

    for (int i = 0; i <= 50009; i++) {
        string testSeq = "SEQ_" + string(6 - to_string(i).length(), '0') + to_string(i);
        btree.BTree_insert(testSeq, i);
    }

    // Optional: uncomment this if print is implemented
    // btree.BTree_print();

    cout << "[DEBUG] Insert test complete." << endl;
    return 0;
}
