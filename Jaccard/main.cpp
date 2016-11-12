#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <set>
#include <queue>
#include <algorithm>

using namespace std;

void read(std::ifstream & in, std::string & string, int streamsize) {
    int pos=0;
    while(pos < streamsize){
        in.get(string[pos]);
        ++pos;
    }
}

// Params:(name of document, queue for shingles (maybe better other structure), k)



void file_shingling(string file, vector<string> &shingles, int k) {
    set<string> control;
    ifstream fIn(file, ios::in);
    string shingle;
    shingle.resize(k);
    int charPos = 1;
    while(!fIn.eof()) {

        read(fIn, shingle, k);

        if(control.find(shingle) == control.end()) {
            shingles.push_back(shingle);
            control.insert(shingle);
        }

        if(fIn.peek() == '\n') ++charPos;
        if(fIn.eof()) return;
        fIn.seekg(charPos++);

    }
}

int main() {
    string file1, file2;
    cin >> file1 >> file2;
    vector<string> shingles, shingles2;
    int k;
    cin >> k;

    file_shingling(file1, shingles, k);
    file_shingling(file2, shingles2, k);
    vector<string> common_data, union_data;
    sort(shingles.begin(),shingles.end());
    sort(shingles2.begin(),shingles2.end());

    set_intersection(shingles.begin(), shingles.end(), shingles2.begin(), shingles2.end(), std::inserter(common_data, common_data.begin()));

    set_union(shingles.begin(),shingles.end(),shingles2.begin(),shingles2.end(),std::inserter(union_data, union_data.begin()));

    cout << "Jaccard similarity: " << float(common_data.size())/float(union_data.size())<< endl;
}