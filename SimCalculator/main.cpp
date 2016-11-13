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
    cerr << "\t$" << filename << " CALCULATOR INPUT_FILE OUTPUT_FILE k t seed\n";
    cerr << "~~~~~~~~~~~~~~~~\n";
    exit(1);
}

int main(int argc, char *argv[]) {
    string executable_name(argv[0]);
    if (argc != 7) {
        usage(executable_name);
    }

    string calname = string(argv[1]);
    string nameone = string(argv[2]);
    string nametwo = string(argv[3]);
    int k = stoi(string(argv[4]));
    int t = stoi(string(argv[5]));
    int seed = stoi(string(argv[6]));
    bool all = calname == "all";

    if (k < 1) {
        std::cerr << "K value too small! Minimum: 1" << std::endl;
        exit(1);
    }
    ifstream file1(nameone);
    if (file1.fail()) {
        std::cerr << "Unable to open file " << nameone << std::endl;
        exit(1);
    }
    ifstream file2(nametwo);
    if (file2.fail()) {
        std::cerr << "Unable to open file " << nametwo << std::endl;
        exit(1);
    }

    string s1 = utils::file_to_string(file1);
    string s2 = utils::file_to_string(file2);

    clock_t ini;

    if(all || calname == "jaccard_fool") {
        ini = clock();
        Jaccard_fool calculator(s1, s2, k);
        cout << "Jaccard normal: " << calculator.get_similarity() << endl;
        cout << "Exec time: " << double(clock()-ini)/CLOCKS_PER_SEC << endl;
    }
    if (all || calname == "jaccard_hash_order") {
        ini = clock();
        Jaccard_hash_order calculator(s1, s2, k);
        cout << "Jaccard with hashing: " << calculator.get_similarity() << endl;
        cout << "Exec time: " << double(clock()-ini)/CLOCKS_PER_SEC << endl;
    }
    if (all || calname == "minhash") {
        ini = clock();
        cout << "Minhash signature: " << computeMinhash(s1, s2, k, t, seed) << endl;
        cout << "Exec time: " << double(clock()-ini)/CLOCKS_PER_SEC << endl;
    }
}

