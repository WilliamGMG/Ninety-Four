#pragma once

#ifndef NINETY_FOUR_HASHMAP_H
#define NINETY_FOUR_HASHMAP_H

#include <unordered_map>
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <utility>
#include <chrono>
#include <set>
#include "FileLoader.h"
using namespace std;

class HashMap {
private:
    unordered_map<string, set<int>> hashmapBySeq; //key = Sequence, value = vector of IDs

    //Helper Variable for Catch2
    map<string,set<int>> debuggingSequences;

    void insertPrivate(int id, const string& sequence);

    set<int> searchPrivate(int id, const string& sequence);

    void printPrivate();

    //Updates Helper Variables for Catch2
    void updateDebugSeqMap();

    //To avoid Linear Searching values via .find(), use Knuth-Morris-Pratt Algorithm for string searching
    //KMP = returns T if subsequence is found in sequence
    vector<int> getLPS(const string &subsequence);
    bool findKMP(const string &subsequence,const string &sequence);

public:
    //Constructors
    HashMap();
    HashMap(FileLoader& fileLoader);

    //Insert ID with Sequence of new potentially dangerous sample
    void insert(int id, const string& sequence);

    //Getters
    set<int> getIDs(const string& exactSequence); //Returns only exact matches

    //Search by partial sequence (value) -- returns all the IDs that contain the partial sequence
    set<int> search(int id, const string& sequence);

    //Print
    void print();

    //Debugging
    map<string, set<int>> debugSeqMap();
};


#endif //NINETY_FOUR_HASHMAP_H
