#ifndef FILELOADER_H
#define FILELOADER_H

#include <string>
#include <filesystem>
#include <fstream>
#include <utility>
#include <vector>
#include <algorithm>
#include <cctype>
using namespace std;

#define DEFAULT_CHUNK_SIZE 100000

enum class FileSearchStatus {
  Found,
  InvalidFNApath,
  InvalidFolderPath,
  FileNotFoundInFolder
};

enum class LoadChunkStatus {
  Loaded,
  FailedToOpenFile,
  EndOfFile
};

class FileLoader {
public:
  FileLoader(const string& path);
  bool openFile(fstream& file);
  FileSearchStatus findFile();
  FileSearchStatus findFile(const string& path) {this->givenPath = path; return findFile();}
  LoadChunkStatus loadChunk(vector<pair<int, string>>& chunk) {return loadChunk(chunk, this->chunkSize);}
  LoadChunkStatus loadChunk(vector<pair<int, string>>& chunk, int chunkSize);
  string getFileHeader();
  void setChunkSize(int size) {this->chunkSize = size;}
  void resetFilePos() {currentLine = 1; uid = 1;}
  int getSequenceLength();

private:
  int uid;
  string givenPath;
  string filePath;
  int chunkSize;
  int currentLine;
};

#endif //FILELOADER_H
