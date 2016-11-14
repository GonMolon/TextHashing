#ifndef A_TEXTHASHING_LSH
#define A_TEXTHASHING_LSH

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <cmath>
#include <string>
#include <unordered_map>
#include <set>
#include "../SimCalculator/Minhash.cpp"
#include "../SimCalculator/Utils.cpp"
using namespace std;

int get_b(int l, int r, int t, double min) {
    double b = ((l+r)/2);
    if(b == l || b == r) {
        return b;
    }
    long double aux = pow((1/b), (b/t));
    if(min*0.9 <= aux && aux <= min*1.1) {
        return b;
    } else if(aux > min) {
        return get_b(b, r, t, min);
    } else {
        return get_b(l, b, t, min);
    }
}

typedef pair<int, int> candidate;

struct candidates {

    set<candidate> s;

    void insert(int id1, int id2) {
        if(id1 > id2) {
            int aux = id1;
            id1 = id2;
            id2 = aux;
        }
        s.insert(candidate(id1, id2));
    }
};

typedef unordered_map<int, vector<int> > clusters;

void treatCandidates(const vector<string>& names, const candidates& c, const vector<signature>& m) {
    set<candidate>::iterator i = c.s.begin();
    while(i != c.s.end()) {
        cout << "-------------------" << endl;
        cout << names[i->first] << endl;
        cout << names[i->second] << endl;
        cout << "Real sim = " << computeSim(m[i->first], m[i->second]) << endl;
        ++i;
    }
}

void computeLSH(const vector<string>& names, const vector<string>& files, int k, int t, double min, int seed) {
    int b = get_b(1, t-1, t, min);
    int r = t/b;
    t = r*b;
    cout << "b = " << b << endl;
    cout << "r = " << r << endl;
    cout << "t = " << t << endl;
    vector<Hash> hashes = generateHashes(t, seed);
    vector<signature> m(files.size());
    for(int i = 0; i < m.size(); ++i) {
        m[i] = generateSignature(k, (files[i]), hashes, true);
        for(int j = 0; j < m[i].size(); ++j) {
            cout << m[i][j] << ' ';
        }
        cout << endl;
    }
    candidates c;
    for(int i = 0; i < b; ++i) {
        clusters cls;
        for(int j = 0; j < m.size(); ++j) {
            int h = 0;
            for(int k = 0; k < r; ++k) {
                h += m[j][i*r+k];
            }
            clusters::iterator it = cls.find(h);
            if(it != cls.end()) {
                for(int l = 0; l < it->second.size(); ++l) {
                    c.insert(j, it->second[l]);
                }
                it->second.push_back(j);
            } else {
                cls.insert(pair<int, vector<int> >(h, vector<int>(1, j)));
            }
        }
    }
    treatCandidates(names, c, m);
}

void usage(const std::string &filename) {
    cerr << "LSH usage:\n";
    cerr << "\t$" << filename << " PATH_PATTERN k t seed\n";
    cerr << "~~~~~~~~~~~~~~~~\n";
    exit(1);
}

int main(int argc, char *argv[]) {
    string exec_name(argv[0]);
    if(argc != 6) {
        usage(exec_name);
    }
    string pattern = string(argv[1]);
    int k = stoi(string(argv[2]));
    int t = stoi(string(argv[3]));
    double min = atof(argv[4]);
    int seed = stoi(string(argv[5]));

    vector<string> names;
    vector<string> files;
    int i = 1;
    string path = pattern + to_string(i) + ".txt";
    ifstream file(path);
    while(!file.fail()) {
        names.push_back(utils::getFileName(path));
        files.push_back(utils::file_to_string(file));
        if(files[files.size()-1].size() < k) {
            cerr << "At least one file has length < k" << endl;
            exit(1);
        }
        ++i;
        path = pattern + to_string(i) + ".txt";
        file = ifstream(path);
    }
    if(i <= 2) {
        cerr << "Files not found" << endl;
        exit(1);
    }
    computeLSH(names, files, k, t, min, seed);
}

#endif
