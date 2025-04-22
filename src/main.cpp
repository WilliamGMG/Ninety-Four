#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <set>

#include "FileLoader.h"
#include "BTree.h"

using namespace std;

int main() {
    string path;
    cout << "Please enter a path to a folder or .fna file: ";
    cin >> path;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    FileLoader fileLoader(path);
    FileSearchStatus searchStatus = fileLoader.findFile();

    while (searchStatus != FileSearchStatus::Found) {
        if (searchStatus == FileSearchStatus::InvalidFileType) {
            cout << "Invalid file type!" << endl;
        } else if (searchStatus == FileSearchStatus::InvalidFolderPath) {
            cout << "Invalid folder path!" << endl;
        } else if (searchStatus == FileSearchStatus::InvalidFNApath) {
            cout << "Invalid file path!" << endl;
        } else if (searchStatus == FileSearchStatus::FileNotFoundInFolder) {
            cout << ".fna file not found in folder!" << endl;
        }
        cout << "Please enter a path to a folder or .fna file: ";
        cin >> path;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        fileLoader = FileLoader(path);
        searchStatus = fileLoader.findFile();
    }

    cout << ".fna file found!" << endl;

    BTree btree;

    cout << "[DEBUG] Loading file into B-tree..." << endl;
    btree.load_file(fileLoader);
    cout << "[DEBUG] File load complete." << endl;

    // Optional: test known inserts at high ID range
    /*
    for (int i = 49990; i < 50020; i++) {
        string testSeq = "SEQ_" + to_string(i);
        btree.BTree_insert(testSeq, i);
    }
    */

    string seq;
    cout << endl << "Please enter a sequence to search for: ";
    cin >> seq;

    while (seq != "exit") {
         set<int> results = btree.search(seq);

         if (results.empty()) {
             cout << "No matching sequence found." << endl;
         } else {
             cout << "Scan complete:" << endl;
             for (int id : results) {
                 cout << "\tSeq. match at ID: " << id << endl;
             }
         }

         cout << endl << "Please enter a sequence to search for or exit to end: ";
         cin >> seq;
    }

    return 0;
}
