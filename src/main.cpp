#include <iostream>
#include <string>
#include <vector>
#include <utility>

#include "FileLoader.h"

using namespace std;

// Search here: https://www.ncbi.nlm.nih.gov/datasets/genome/

int main() {
  FileLoader file("../data/Human/");
  FileSearchStatus fileStatus = file.findFile();

  vector<pair<int, string>> chunk;
  file.setChunkSize(500);

  LoadChunkStatus loadStatus = file.loadChunk(chunk);
  for (auto [fst, snd] : chunk) {
    cout << "ID: " << fst << " Seq: " << snd << endl;
  }

  loadStatus = file.loadChunk(chunk, 1000);
  for (auto [fst, snd] : chunk) {
    cout << "ID: " << fst << " Seq: " << snd << endl;
  }

  return 0;
}