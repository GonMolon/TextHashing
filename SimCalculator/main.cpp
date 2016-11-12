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

int main(int argc, char *argv[]) {
    string executable_name(argv[0]);
    if (argc < 5) {
        usage(executable_name);
    }

    string calname = string(argv[1]);
    string nameone = string(argv[2]);
    string nametwo = string(argv[3]);
    int k = stoi(string(argv[4]));
    bool all = calname == "all";
    if(all || calname == "jaccard_fool") {
        Jaccard_fool calculator(nameone, nametwo, k);
        cout << k << "\t" << calculator.get_time() << "\t" << calculator.get_similarity();
        cout << endl;
    }
    if (all || calname == "jaccard_hash_order") {
        Jaccard_hash_order calculator(nameone, nametwo, k);
        cout << k << "\t" << calculator.get_time() << "\t" << calculator.get_similarity();
        cout << endl;
    }
    if (all || calname == "minhash") {

    }
}

