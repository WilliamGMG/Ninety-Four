#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <set>
#include <limits>

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

  //Create BTree's and HashMaps
  vector<BTree*> bTrees;
  vector<HashMap*> hashMaps;
  int maxSequenceLength = INT_MAX;
  for (auto fileLoader : fileLoaders) {
    auto* newBTree = new BTree();
    newBTree->load_file(fileLoader);
    fileLoader.resetFilePos();

    auto* newHashMap = new HashMap(fileLoader);
    fileLoader.resetFilePos();
    bTrees.push_back(newBTree);
    hashMaps.push_back(newHashMap);

    int newSeqLen = fileLoader.getSequenceLength();
    if (newSeqLen < maxSequenceLength) {
      maxSequenceLength = newSeqLen;
    }
  }

  // Print organisms
  cout << endl << "Organism files loaded: " << endl;
  for (auto f : fileLoaders) {
    cout << "\t" << f.getFileHeader() << endl;
  }

  bool lineNum;
  string option;
  cout << endl << "Option: Would you like to know the line number of the sequence?\nEnter \"yes\" for yes or anything else for no: ";
  cin >> option;
  if (option == "yes") {
    lineNum = true;
  } else {
    lineNum = false;
  }

  // Max sequence length
  cout << endl << "Note: Sequences entered have to be less than " << maxSequenceLength << " characters long." << endl;

  // Get and search for sequences
  string seq;
  while (true) {
    cout << "Please enter a sequence to search for or \"exit\" to exit: ";
    cin >> seq;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (seq == "exit") {
      break;
    }

    if (seq.length() > maxSequenceLength) {
      cout << "That sequence is too big!" << endl;
      continue;
    }

    // Search for the sequence in each BTree / HashMap
    for (int i = 0; i < fileLoaders.size(); i++) {
      // Header
      cout << fileLoaders[i].getFileHeader() << endl;
      cout << "BTree search:" << endl;

      // BTree
      auto t1= chrono::high_resolution_clock::now();
      auto results = bTrees[i]->search(seq);
      bool found = !results.empty();
      auto t2 = chrono::high_resolution_clock::now();

      if (found) {
        if (lineNum) {
          string lineNumbers = "";
          for (auto num : results) {
            lineNumbers += to_string(num+1) + ", ";
          }
          lineNumbers.pop_back();
          lineNumbers.pop_back();
          cout << "\tFound on line number(s): " << lineNumbers << endl;
        } else {
          cout << "\tFound." << endl;
        }
      } else {
        cout << "\tNot found." << endl;
      }
      cout << "\tSearch time: " << chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count() << "ms" << endl;

      // HashMap
      cout << "Hash map search:" << endl;

      t1= chrono::high_resolution_clock::now();
      results = hashMaps[i]->search(1, seq);
      found = !results.empty();
      t2 = chrono::high_resolution_clock::now();

      if (found) {
        if (lineNum) {
          string lineNumbers = "";
          for (auto num : results) {
            lineNumbers += to_string(num+1) + ", ";
          }
          lineNumbers.pop_back();
          lineNumbers.pop_back();
          cout << "\tFound on line number(s): " << lineNumbers << endl;
        } else {
          cout << "\tFound." << endl;
        }
      } else {
        cout << "\tNot found." << endl;
      }
      cout << "\tSearch time: " << chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count() << "ms" << endl << endl;
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