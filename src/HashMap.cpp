#include "HashMap.h"

//Constructor
HashMap::HashMap() = default;
//Parameterized
HashMap::HashMap(vector<pair<int, string>> &chunks) {
    for (auto &i:chunks){
        genomeHashmap[i.first] = i.second;
    }
}

//Insert
//Citation: https://en.cppreference.com/w/cpp/container/unordered_map/insert
void HashMap::insert(int id, const string &sequence) {
    insertPrivate(id, sequence);
}
void HashMap::insertPrivate(int id, const string &sequence) {
    genomeHashmap.insert({id,sequence});
}

//Search
//Citation: https://cplusplus.com/reference/unordered_map/unordered_map/find/
vector<int> HashMap::search(int id, const string &sequence) {
    return searchPrivate(id, sequence);
}
vector<int> HashMap::searchPrivate(int id, const string &sequence) {
    vector<int> resultIDs; //contains the IDs that have the partial sequence within the stored sequences

    //Iterate through and check if sequence is within any values
    for (auto & specimen : genomeHashmap){

        //Citation: https://cplusplus.com/reference/string/string/find/
        if (specimen.second.find(sequence) != string::npos){
            resultIDs.push_back(specimen.first);
        }
    }

    //IDs were found, insert new specimen that we were searching for
    if (!resultIDs.empty()){
        insertPrivate(id,sequence);
    }

    return resultIDs;
}

//Printing and Traversals
void HashMap::print() {
    printPrivate();
}
void HashMap::printPrivate() {
    for (auto & specimen : genomeHashmap){
        cout << "ID: " << specimen.first << ": " << specimen.second << endl;
        }
    }

map<int, string> HashMap::debugMap() {
    updateDebugMap();
    return debuggingIDs;
}

void HashMap::updateDebugMap() {
    for (auto & specimen : genomeHashmap){
        debuggingIDs[specimen.first] = specimen.second;
    }
}

vector<int> HashMap::getIDs(const string &exactSequence) {
    vector<int> resultIDs; //contains the IDs that have the partial sequence within the stored sequences

    //Iterate through and check if for exactSequence
    for (auto & specimen : genomeHashmap){
        if (specimen.second == exactSequence){
            resultIDs.push_back(specimen.first);
        }
    }
    return resultIDs;
}

string HashMap::getSequence(const int &ID) {
    return genomeHashmap[ID];
}
