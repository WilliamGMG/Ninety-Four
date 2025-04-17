#include "FileLoader.h"

FileLoader::FileLoader(const string& path) {
    this->givenPath = path;
    this->filePath = "";
    this->uid = 1;
    this->chunkSize = 1;
    this->currentLine = 1;
}

// Verify the path and check the folder for a .fna fill if a folder is given
FileSearchStatus FileLoader::findFile() {
    // Check if the path has the .fna extension
    if (givenPath.substr(givenPath.size() - 4, 4) == ".fna") {
        if (filesystem::exists(givenPath)) {
            filePath = givenPath;
            replace(filePath.begin(), filePath.end(), '\\', '/');
            return FileSearchStatus::Found;
        }
        return FileSearchStatus::InvalidFNApath;
    }
    if (givenPath.find('.') != string::npos && givenPath.find("..") == string::npos) { // Path to file that is not .fna
        return FileSearchStatus::InvalidFileType;
    }

    if (!filesystem::exists(givenPath)) {
        return FileSearchStatus::InvalidFolderPath;
    }

    // Search folder / subdirectories for .fna file
    for (const auto& entry : filesystem::recursive_directory_iterator(givenPath)) {
        if (entry.is_regular_file() && entry.path().extension() == ".fna") {
            filePath = entry.path().string();
            replace(filePath.begin(), filePath.end(), '\\', '/');
            return FileSearchStatus::Found;
        }
    }

    if (filePath == "") {
        return FileSearchStatus::FileNotFoundInFolder;
    }

    return FileSearchStatus::Found;
}

// All the strings are in all caps
LoadChunkStatus FileLoader::loadChunk(vector<pair<int, string>>& chunk, int chunkSize) {
    fstream file;
    if (!openFile(file)) {
        return LoadChunkStatus::FailedToOpenFile;
    }
    chunk.clear();

    //Skip already read lines
    string line;
    for (int i = 0; i < currentLine; i++) {
        if (file.eof()) {
            return LoadChunkStatus::EndOfFile;
        }
        getline(file, line);
    }

    // Go until chunk size
    for (int i = 0; i < chunkSize; i++) {
        if (file.eof()) {
            return LoadChunkStatus::EndOfFile;
        }
        getline(file, line);
        if (line != "") {
            transform(line.begin(), line.end(), line.begin(), ::toupper);
            chunk.push_back(make_pair(uid, line));
        }
        uid++;
        currentLine++;
    }

    file.close();
    return LoadChunkStatus::Loaded;
}

bool FileLoader::openFile(fstream& file) {
    try {
        if (!filesystem::exists(this->givenPath)) {
            return false;
        }

        file.open(filePath);
        if (!file.is_open()) {
            return false;
        }
    } catch (const exception& e) {
        return false;
    }
    return true;
}