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
using namespace std;

//FIXME: potential issue with ID from hashmap not making sense with the inserted ID?
class HashMap {
private:
    unordered_map<int, string> genomeHashmap; // key = ID, string =  capitalized string of letters
    std::chrono::duration<float, std::milli> searchTime; //Citation: https://cplusplus.com/reference/chrono/duration/duration/

    map<int,string> debuggingIDs; //helper variable for Catch2

    //if searched and found, add the newID to the hashMap and rehash if necessary
    void insertPrivate(int id, const string& sequence);

    vector<int> searchPrivate(int id, const string& sequence);

    void printPrivate();

    void updateDebugMap(); //updates the debuggingIDs for Catch2 purposes

public:
    //Constructors
    HashMap();
    //FIXME: Parameterized to add a lot of keys at once
    HashMap(vector<pair<int, string>> &chunks);

    //Insert ID with Sequence of new potentially dangerous sample
    void insert(int id, const string& sequence);

    //Getters
    vector<int> getIDs(const string& exactSequence); //Finds keys with the EXACT sequence match
    string getSequence(const int& ID);

    //Search by partial sequence (value) -- returns all the IDs that contain the partial sequence
    vector<int> search(int id, const string& sequence);

    //Print
    void print();

    //Debugging
    map<int,string> debugMap();
};


#endif //NINETY_FOUR_HASHMAP_H
