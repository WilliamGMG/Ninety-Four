#include <iostream>
#include <string>
#include <vector>
#include <utility>

#include "FileLoader.h"
#include <set>
#include "BTree.h"

using namespace std;

// Search here: https://www.ncbi.nlm.nih.gov/datasets/genome/

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
  }
  cout << ".fna file found!" << endl;

  string seq;
  BTree btree;
  btree.load_file(fileLoader);

  cout << endl << "Please enter a sequence to search for: ";
  cin >> seq;
  while (seq != "exit") {
    // Filler code. here is where main with interact with the B Tree and hash table
    set<int> tree = btree.BTree_search(seq);
    if (tree.empty() == false) {
      cout << "Scan complete:" << endl;
      for (set<int>::iterator it = tree.begin(); it != tree.end(); it++) {
        cout << "\tSeq. match at ID: " << *it << endl;
      }

    }

    // End filler code.
    cout << endl << "Please enter a sequence to search for or exit to end: ";
    cin >> seq;
  }

  return 0;
}