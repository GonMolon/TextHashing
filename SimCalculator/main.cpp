#include <iostream>
#include <vector>
#include <fstream>
#include <set>
#include <queue>
#include <algorithm>
#include "Jaccard.cpp"
#include "Minhash.cpp"

using namespace std;

void readFile(std::ifstream& in, std::string& string, int streamsize) {
    int pos=0;
    while(pos < streamsize){
        in.get(string[pos]);
        ++pos;
    }
}

// Params:(name of document, queue for shingles (maybe better other structure), k)

vector<string> file_shingling(string file, int k) {
    vector<string> shingles;
    set<string> control;
    ifstream fIn(file, ios::in);
    string shingle;
    shingle.resize(k);
    int charPos = 1;
    while(!fIn.eof()) {

        readFile(fIn, shingle, k);

        if(control.find(shingle) == control.end()) {
            shingles.push_back(shingle);
            control.insert(shingle);
        }

        if(fIn.peek() == '\n') ++charPos;
        if(fIn.eof()) return shingles;
        fIn.seekg(charPos++);

    }
    return shingles;
}

int main(int argc, char *argv[]) {
    string file1 = argv[1];
    string file2 = argv[2];
    int k;
    cin >> k;

    vector<string> shingles1 = file_shingling(file1, k);
    vector<string> shingles2 = file_shingling(file2, k);

    cout << "Jaccard similarity: " << computeJaccard(shingles1, shingles2) << endl;
    cout << "Minhash similarity: " << computeMinhash(shingles1, shingles2) << endl;
}

