#include <iostream>
#include <vector>
#include <fstream>
#include <set>
#include <queue>
#include <algorithm>
#include "Jaccard_fool.cpp"
#include "Jaccard_hash_order.cpp"
#include "Jaccard_hash_roll.cpp"
#include "Minhash.cpp"
#include "LSH.cpp"

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

    if(s1.size() < k || s2.size() < k) {
        cout << "k cannot be greater than the size of any document" << endl;
        exit(1);
    }

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
    if (all || calname == "jaccard_hash_roll") {
        ini = clock();
        Jaccard_hash_roll calculator(s1, s2, k);
        cout << "Jaccard with rolling hashing: " << calculator.get_similarity() << endl;
        cout << "Exec time: " << double(clock()-ini)/CLOCKS_PER_SEC << endl;
    }
    if (all || calname == "minhash") {
        ini = clock();
        cout << "Minhash signature: " << computeMinhash(s1, s2, k, t, seed, false) << endl;
        cout << "Exec time: " << double(clock()-ini)/CLOCKS_PER_SEC << endl;
    }
    if (all || calname == "minhash_roll") {
        ini = clock();
        cout << "Minhash signature (with rollinghash): " << computeMinhash(s1, s2, k, t, seed, true) << endl;
        cout << "Exec time: " << double(clock()-ini)/CLOCKS_PER_SEC << endl;
    }
    if(all || calname == "lsh") {
        ini = clock();
        vector<string> names;
        vector<string*> files;
        names.push_back(nameone);
        names.push_back(nametwo);
        files.push_back(&s1);
        files.push_back(&s2);
        cout << "LSH sim pairs: ";
        //vector<pair<pair<string, string>, double> > result = computeLSH(names, files, k, t, seed);
        cout << "Exec time: " << double(clock()-ini)/CLOCKS_PER_SEC << endl;
    }
}

