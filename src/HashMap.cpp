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
    //Citation: https://en.cppreference.com/w/cpp/chrono/high_resolution_clock/now & Module 2 Study Guide
    auto t1= std::chrono::high_resolution_clock::now();
    vector<int> resultVector = searchPrivate(id,sequence);
    auto t2 = std::chrono::high_resolution_clock::now();
    searchTime = t2 - t1;
    return resultVector;
}
vector<int> HashMap::searchPrivate(int id, const string &sequence) {
    vector<int> resultIDs; //contains the IDs that have the partial sequence within the stored sequences

    //Iterate through and check if sequence is within any values
    for (auto & specimen : genomeHashmap){
        if (findKMP(sequence,specimen.second)){
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

//Citation: https://www.youtube.com/watch?v=GTJr8OvyEVQ, https://www.youtube.com/watch?v=V5-7GzOfADQ
vector<int> HashMap::getLPS(const string &subsequence) {
    //EdgeCase Sequence DNE -- return empty vector
    if (subsequence.empty()){return {};}

    //Initialize Longest Prefix Suffix Array
    vector<int> lps(subsequence.size(),0);

    //Adjustments to LPS where i and j are index pointers
    int i = 0;
    int j = 1;
    while (j < subsequence.size()){
        if (subsequence[j] == subsequence[i]){
            lps[j] = i + 1;
            i++;
            j++;
        }
        else{ //not a matching character
            if (i != 0){
                //use value to the left of the left pointer
                i = lps[i - 1];
            }
            else{ //no match, set to 0 and increment
                lps[j] = 0;
                j++;
            }
        }
    }
    return lps;
}
bool HashMap::findKMP(const string &subsequence, string &sequence) {
    bool result = false; //change to true the moment subsequence is found

    //Edge Case -- if either sequence DNE
    if (subsequence.empty() || sequence.empty()){return result;}

    //KMP -- return true at the first instance of the subsequence being in the sequence
    vector<int> lps = getLPS(subsequence);
    //set up pointers for the sequences
    int subSeq = 0;
    int seq = 0;

    while(seq < sequence.size()){
        //Matching Characters
        if (subsequence[subSeq] == sequence[seq]){
            subSeq++;
            seq++;
            if (seq == subsequence.size()){
                return true;
            }
        }
        //Characters do not match, skip indices in next pass
        else{
            if (subSeq == 0){
                seq++;
            }
            else{
                subSeq = lps[subSeq - 1];
            }
        }
    }

    return result; //Catch-all in case
}