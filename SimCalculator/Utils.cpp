#ifndef A_TEXTHASHING_UTILITIES
#define A_TEXTHASHING_UTILITIES

#include <fstream>
using namespace std;

string filetostring(ifstream &file) {
    string str;
    str.assign( (std::istreambuf_iterator<char>(file) ),
                (std::istreambuf_iterator<char>()    ) );
    return str;
}

/*
MAGI:

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
 */

#endif