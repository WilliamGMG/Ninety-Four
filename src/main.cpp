#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <set>

#include "FileLoader.h"
#include "HashMap.h"
#include "BTree.h"

using namespace std;

// Search here for genomes to download here: https://www.ncbi.nlm.nih.gov/datasets/genome/

int main() {

  // Get .fna files
  string path;
  vector<FileLoader> fileLoaders;
  set<string> validFiles;

  while (true) {
    // Get path
    cout << "Please enter a path to a .fna file or \"next\" to continue: ";
    cin >> path;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // Edge cases
    if (path == "next" && fileLoaders.empty()) {
      cout << "Cannot continue without a valid file path!" << endl;
      continue;
    }
    if (path == "next") {
      break;
    }
    if (validFiles.count(path)) {
      cout << "File already entered!" << endl;
      continue;
    }

    // Try to find file
    FileLoader newFileLoader(path);
    const FileSearchStatus searchStatus = newFileLoader.findFile();

    // Check if it was successful
    if (searchStatus == FileSearchStatus::InvalidFolderPath) {
      cout << "Path does not exist!" << endl;
      continue;
    }
    if (searchStatus == FileSearchStatus::InvalidFNApath) {
      cout << "Invalid file path!" << endl;
      continue;
    }
    if (searchStatus == FileSearchStatus::FileNotFoundInFolder) {
      cout << ".fna file not found in folder!" << endl;
      continue;
    }

    validFiles.insert(path);
    fileLoaders.push_back(newFileLoader);
    cout << "File found!" << endl;
  }

  // Print organisms
  cout << endl << "Organism files loaded: " << endl;
  for (auto f : fileLoaders) {
    cout << "\t" << f.getFileHeader() << endl;
  }

  //Create BTree's and HashMaps
  vector<BTree*> bTrees;
  vector<HashMap*> hashMaps;
  for (auto fileLoader : fileLoaders) {
    auto* newBTree = new BTree(fileLoader);
    fileLoader.resetFilePos();
    auto* newHashMap = new HashMap(fileLoader);
    fileLoader.resetFilePos();
    bTrees.push_back(newBTree);
    hashMaps.push_back(newHashMap);
  }

  // Get and search for sequences
  string seq;

  while (true) {
    cout << endl;
    cout << "Please enter a sequence to search for: ";
    cin >> seq;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (seq == "exit") {
      break;
    }

    // Search for the sequence in each BTree / HashMap
    for (int i = 0; i < fileLoaders.size(); i++) {
      // Header
      cout << fileLoaders[i].getFileHeader() << endl;
      cout << "\tBTree search: ";

      // BTree
      auto t1= chrono::high_resolution_clock::now();
      bool found = !bTrees[i]->BTree_search(seq).empty();
      auto t2 = chrono::high_resolution_clock::now();

      if (found) {
        cout << "found." << endl;
      } else {
        cout << "not found." << endl;
      }
      cout << "\tBTree search time: " << chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count() << "ms" << endl;

      // HashMap
      cout << "\tHash map search: ";

      t1= chrono::high_resolution_clock::now();
      found = !hashMaps[i]->search(1, seq).empty();
      t2 = chrono::high_resolution_clock::now();

      if (found) {
        cout << "found." << endl;
      } else {
        cout << "not found." << endl;
      }
      cout << "\tHash map search time: " << chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count() << "ms" << endl;
    }
  }

  // Delete data structures
  for (auto bTree : bTrees) {
    delete bTree;
  }
  for (auto hashMap : hashMaps) {
    delete hashMap;
  }

  return 0;
}