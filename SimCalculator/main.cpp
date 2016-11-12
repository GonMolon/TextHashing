#include <iostream>
#include <vector>
#include <fstream>
#include <set>
#include <queue>
#include <algorithm>
#include "Jaccard_hash_order.cpp"
#include "Jaccard_fool.cpp"
#include "Minhash.cpp"

using namespace std;

void usage(const std::string &filename) {
    cerr << "SimCalculator usage:\n";
    cerr << "\t$" << filename << " CALCULATOR INPUT_FILE OUTPUT_FILE K\n";
    cerr << "~~~~~~~~~~~~~~~~\n";
    exit(1);
}

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
    string executable_name(argv[0]);
    if (argc < 5) {
        usage(executable_name);
    }

    string calname = string(argv[1]);
    string nameone = string(argv[2]);
    string nametwo = string(argv[3]);
    int k = stoi(string(argv[4]));
    if (calname == "all") {

    }
    else if (calname == "jaccard_fool") {
        Jaccard_fool calculator(nameone, nametwo, k);
        cout << k << "\t" << calculator.get_time() << "\t" << calculator.get_similarity();
        cout << endl;
    }
    else if (calname == "jaccard_hash_order") {
        Jaccard_hash_order calculator(nameone, nametwo, k);
        cout << k << "\t" << calculator.get_time() << "\t" << calculator.get_similarity();
        cout << endl;
    }
    else if (calname == "minhash") {

    }
    else {
        usage(executable_name);
    }
}

