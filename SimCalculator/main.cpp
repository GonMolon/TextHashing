#include <algorithm>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <list>
#include <random>
#include <vector>

#include "Jaccard_fool.cpp"
#include "Jaccard_hash_order.cpp"
#include "Jaccard_hash_roll.cpp"
#include "man.cpp"
#include "Minhash.cpp"

using namespace std;

void usage () {
    cout << "===========================" << endl;
    cerr << "Usage: " << endl << endl;
    cerr << "    ./SimCalculator FILE_ONE FILE_TWO MODE" << endl;
    cerr << endl;
    cerr << "    Possible MODEs are:" << endl;
    cerr << endl << bold_on;
    cerr << "        jaccard" << endl;
    cerr << endl;
    cerr << "        jaccard_hash" << endl;
    cerr << endl;
    cerr << "        jaccard_roll" << endl;
    cerr << endl;
    cerr << "        minhash" << endl;
    cerr << endl;
    cerr << "        minhash_roll" << endl << bold_off;
    cout << endl;
    cerr << "Execute \"./SimCalculator help\" for an extended help section." << endl;
    cout << "===========================" << endl;
    exit(1);
}

int main(int argc, char *argv[]) {
    if (argc == 2 && string(argv[1]) == "help") {
        man();
    }
    if (argc < 4) {
        usage();
    }

    // Default values
    int k, t, seed;
    bool e;
    seed = random_device()();
    k = 9;
    t = -1;
    e = false;

    // FILE_ONE FILE_TWO MODE
    string nameone = string(argv[1]);
    string nametwo = string(argv[2]);
    string calname = string(argv[3]);
    bool all = calname == "all";
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

    // PARAMETERS
    for (int i = 4; i < argc; ++i) {
        string param(argv[i]);
        if (param == "-e") {
            e = true;
        }
        else {
            int param_size = (uint)param.size();
            if (param_size >= 5) {
                uint i_eq = (uint) param.find('=');
                if (i_eq + 2 <= param_size) {
                    string name = param.substr(0, i_eq);
                    if (name == "--k") {
                        k = stoi(param.substr(i_eq + 1, param_size - i_eq - 1));
                    }
                    else if (name == "--t") {
                        t = stoi(param.substr(i_eq + 1, param_size - i_eq - 1));
                    }
                    else if (name == "--seed") {
                        seed = stoi(param.substr(i_eq + 1, param_size - i_eq - 1));
                    }
                }
            }
        }
    }

    if (k < 1) {
        std::cerr << "K value too small! Minimum: 1" << std::endl;
        exit(1);
    }

    string s1 = utils::file_to_string(file1);
    string s2 = utils::file_to_string(file2);
    if(s1.size() < k || s2.size() < k) {
        cout << "k cannot be greater than the size of any document" << endl;
        exit(1);
    }

    clock_t ini;

    bool mode_found = false;
    double similarity, time;
    list< tuple<string, double, double> > results;
    if(all || calname == "jaccard") {
        mode_found = true;
        ini = clock();
        Jaccard_fool calculator(s1, s2, k);
        time = double(clock()-ini)/CLOCKS_PER_SEC;
        similarity = calculator.get_similarity();
        results.push_back(tuple<string, double, double>("jaccard", similarity, time));
    }
    if (all || calname == "jaccard_hash") {
        mode_found = true;
        ini = clock();
        Jaccard_hash_order calculator(s1, s2, k);
        time = double(clock()-ini)/CLOCKS_PER_SEC;
        similarity = calculator.get_similarity();
        results.push_back(tuple<string, double, double>("jaccard_hash", similarity, time));
    }
    if (all || calname == "jaccard_roll") {
        mode_found = true;
        ini = clock();
        Jaccard_hash_roll calculator(s1, s2, k);
        time = double(clock()-ini)/CLOCKS_PER_SEC;
        similarity = calculator.get_similarity();
        results.push_back(tuple<string, double, double>("jaccard_roll", similarity, time));
    }
    if (all || calname == "minhash") {
        if (t < 1) {
            cerr << endl;
            cerr << "You must provide a parameter --t=POSITIVE_INTEGER parameter for minhash modes!" << endl << endl;
            exit(1);
        }
        mode_found = true;
        ini = clock();
        similarity = computeMinhash(s1, s2, k, t, seed, false);
        time = double(clock()-ini)/CLOCKS_PER_SEC;
        results.push_back(tuple<string, double, double>("minhash", similarity, time));
    }
    if (all || calname == "minhash_roll") {
        if (t < 1) {
            cerr << endl;
            cerr << "You must provide a parameter --t=POSITIVE_INTEGER parameter for minhash modes!" << endl << endl;
            exit(1);
        }
        mode_found = true;
        ini = clock();
        similarity = computeMinhash(s1, s2, k, t, seed, true);
        time = double(clock()-ini)/CLOCKS_PER_SEC;
        results.push_back(tuple<string, double, double>("minhash_roll", similarity, time));
    }

    if (!mode_found) {
        usage();
    }

    if (e) {
        cout << setw(12) << "MODE" << setw(14) << "SEED" << setw(5) << "K" << setw(5) << "T";
        cout << setw(13) << "SIM" <<  setw(13) << "TIME" << endl;
    }
    else {
        cout << "===========================" << endl;
    }
    cout.precision(8);
    for (auto it = results.begin(); it != results.end(); ++it) {
        if (e) {
            cout << setw(12) << get<0>(*it) << setw(14) << seed << setw(5) << k << setw(5) << t;
            cout << setw(13) << fixed << get<1>(*it) <<  setw(13) << fixed << get<2>(*it) << endl;
        }
        else {
            cout << uline_on << get<0>(*it) << uline_off << endl;
            cout << "time: " << setw(21) << fixed << get<2>(*it) << endl;
            cout << "similarity: " << setw(15) << fixed << get<1>(*it) << endl;
            cout << "===========================" << endl;
        }
    }
}

