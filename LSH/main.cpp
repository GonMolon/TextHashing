#ifndef A_TEXTHASHING_LSH
#define A_TEXTHASHING_LSH

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <cmath>
#include <unordered_map>
#include <set>
#include <dirent.h>
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

void treatCandidates(const vector<string>& names, const candidates& c, const vector<signature>& m, double min) {
    int falsePositives = 0;
    cout << "------------------------------------------------------------------" << endl;
    cout << "The follow pair of files may have a similarity greater than  " << min << endl;
    set<candidate>::iterator i = c.s.begin();
    while(i != c.s.end()) {
        cout << "------------------------------------------------------------------" << endl;
        cout << names[i->first] << endl;
        cout << names[i->second] << endl;
        double realSim = computeSim(m[i->first], m[i->second]);
        cout << "Real similarity = " << realSim << endl;
        if(realSim < min) {
            ++falsePositives;
            cout << "FALSE POSITIVE" << endl;
        }
        ++i;
    }
    cout << "------------------------------------------------------------------" << endl;
    cout << "Total of false positives = " << falsePositives << endl;
}

void computeLSH(const vector<string>& names, const vector<string>& files, int k, int t, double min, int seed) {
    int b = get_b(1, t-1, t, min);
    int r = t/b;
    if(t != r*b) {
        cout << "A new t has been fixed to be able to execute the algorithm properly." << endl;
    }
    cout << "The final values are: " << endl;
    t = r*b;
    cout << "b = " << b << endl;
    cout << "r = " << r << endl;
    cout << "t = " << t << endl;
    vector<Hash> hashes = generateHashes(t, seed);
    vector<signature> m(files.size());
    for(int i = 0; i < m.size(); ++i) {
        m[i] = generateSignature(k, (files[i]), hashes, true);
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
    treatCandidates(names, c, m, min);
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
    string path = string(argv[1]);
    int k = stoi(string(argv[2]));
    int t = stoi(string(argv[3]));
    double min = stof(string(argv[4]));
    int seed = stoi(string(argv[5]));

    if(path.length() == 0) {
        cerr << "Please, provide a path" << endl;
        exit(1);
    }

    if(path[path.size()-1] != '/') {
        path.push_back('/');
    }

    vector<string> names;
    vector<string> files;

    DIR *dir;
    struct dirent *file;

    dir = opendir(path.c_str());
    if(dir != NULL){
        while(file = readdir(dir)){
            if(utils::isTextFile(file->d_name)) {
                names.push_back(file->d_name);
                ifstream is(path + file->d_name);
                files.push_back(utils::file_to_string(is));
                if(files[files.size()-1].size() < k) {
                    cerr << "At least one file has length < k" << endl;
                    exit(1);
                }
            }
        }
        closedir(dir);
        if(files.size() < 2) {
            cerr << "There must be at least 2 .txt files in the path " << path << endl;
            exit(1);
        }
        computeLSH(names, files, k, t, min, seed);
    } else {
        cerr << "Path not found" << endl;
        exit(1);
    }
}

#endif
