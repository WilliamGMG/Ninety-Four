#include <iostream>
#include <string>
#include <vector>
#include <utility>

#include "FileLoader.h"

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

  cout << endl << "Please enter a sequence to search for: ";
  cin >> seq;
  while (seq != "exit") {
    // Filler code. here is where main with interact with the B Tree and hash table
    vector<string> results = {
      "Seq. match at ID: 233544",
      "Seq. match at ID: 123456 to 123458"};
    cout << "Scan complete: " << endl;
    for (auto r : results) {
      cout << "\t" << r << endl;
    }

    // End filler code.
    cout << endl << "Please enter a sequence to search for or exit to end: ";
    cin >> seq;
  }

  return 0;
}