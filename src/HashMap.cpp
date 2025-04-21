#include "HashMap.h"

//Constructor
HashMap::HashMap() = default;
//Parameterized
HashMap::HashMap(FileLoader& fileLoader) {
    vector<pair<int, string>> chunk;

    while (fileLoader.loadChunk(chunk) != LoadChunkStatus::EndOfFile) {
        for (auto &i: chunk) {
            hashmapBySeq[i.second].insert(i.first);
        }
    }
}

//Insert
//Citation: https://en.cppreference.com/w/cpp/container/unordered_map/insert
void HashMap::insert(int id, const string &sequence) {
    insertPrivate(id, sequence);
}
void HashMap::insertPrivate(int id, const string &sequence) {
    //hashmapByID.insert({id, sequence});
    hashmapBySeq[sequence].insert(id);
}

//Search
//Citation: https://cplusplus.com/reference/unordered_map/unordered_map/find/
set<int> HashMap::search(int id, const string &sequence) {
    //Citation: https://en.cppreference.com/w/cpp/chrono/high_resolution_clock/now & Module 2 Study Guide
    auto t1= std::chrono::high_resolution_clock::now();
    set<int> resultVector = searchPrivate(id,sequence);
    auto t2 = std::chrono::high_resolution_clock::now();
    searchTime = t2 - t1;
    return resultVector;
}
set<int> HashMap::searchPrivate(int id, const string &sequence) {
    set<int> resultIDs; //contains the IDs that have the partial sequence within the stored sequences

    //Mixed Hashmap functionality with KMP Algorithm
    for (auto & genome : hashmapBySeq){
        //HashMap Exact Sequences || KMP for substrings
        if (genome.first == sequence || findKMP(sequence,genome.first)){
            resultIDs.insert(genome.second.begin(),genome.second.end());
        }
    }

    return resultIDs;
}

//Printing and Traversals
void HashMap::print() {
    printPrivate();
}
void HashMap::printPrivate() {
    /*
    for (auto & specimen : hashmapByID){
        cout << "ID: " << specimen.first << ": " << specimen.second << endl;
        }
    }
     */
    for (auto & sequence : hashmapBySeq){
        cout << "Sequence: " << sequence.first << ": ";
        for (int i : sequence.second){
            if (i != sequence.second.size() - 1){
                cout << i << ", ";
            }
            else{
                cout << i << endl;
            }
        }
    }}

set<int> HashMap::getIDs(const string &exactSequence) {
    return hashmapBySeq[exactSequence];
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
bool HashMap::findKMP(const string &subsequence,const string &sequence) {
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
            if (subSeq == subsequence.size()){
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

//For Catch2 purposes
map<string, set<int>> HashMap::debugSeqMap() {
    updateDebugSeqMap();
    return debuggingSequences;
}

void HashMap::updateDebugSeqMap() {
    for (auto & seq : hashmapBySeq){
        debuggingSequences[seq.first] = seq.second;
    }
}

/*
map<int, string> HashMap::debugIDMap() {
updateDebugIDMap();
return debuggingIDs;
}

void HashMap::updateDebugIDMap() {
for (auto & specimen : hashmapByID){
    debuggingIDs[specimen.first] = specimen.second;
}

}
*/