#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <set>
#include <queue>
using namespace std;

void read(std::ifstream & in, std::string & string, int streamsize) {
    int pos=0;
    while(pos < streamsize){
        in.get(string[pos]);
        ++pos;
    }
}

// Params:(name of document, queue for shingles (maybe better other structure), k)



void file_shingling(string file, queue<string> &shingles, int k) {
    set<string> control;
    ifstream fIn(file, ios::in);
    string shingle;
    shingle.resize(k);
    int charPos = 1;
    while(!fIn.eof()) {

        read(fIn, shingle, k);

        if(control.find(shingle) == control.end()) {
            shingles.push(shingle);
            control.insert(shingle);
        }
        if(fIn.peek() == '\n') ++charPos;
        if(fIn.eof()) return;
        fIn.seekg(charPos++);
    }
}

int main() {
    string file1;
    cin >> file1;
    queue<string> shingles;
    int k;
    cin >> k;

    file_shingling(file1, shingles, k);


    // Solo esta para mirar que los shingles son correctos
    while(!shingles.empty()){
        cout << shingles.front() << endl;
        shingles.pop();
    }
}