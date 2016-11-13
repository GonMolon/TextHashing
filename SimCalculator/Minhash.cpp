#include <string>
#include <vector>
#include <stdlib.h>
#include <random>
#include <limits.h>
#include <unordered_map>
#include "Utils.cpp"
using namespace std;

typedef unsigned int h_type;
typedef pair<vector<int>, vector<int> > signatures;

class Hash {
private:
    h_type m;
    h_type a;
    h_type b;
    h_type p;

    bool is_prime(h_type x) {
        h_type i = 3;
        while(true) {
            h_type q = x/i;
            if(q < i) {
                return true;
            }
            if(x == q * i) {
                return false;
            }
            i += 2;
        }
    }

    h_type generateNextPrime(h_type n) {
        if(n <= 2) {
            return 2;
        }
        if(!(n & 1)) {
            ++n;
        }
        while(!is_prime(n)) {
            n += 2;
        }
        return n;
    }

public:

    Hash(){}

    Hash(h_type m, h_type u, int seed) {
        this->m = m;
        p = generateNextPrime(u);

        mt19937 rng(seed);
        uniform_int_distribution<h_type> distA(1, p-1);
        uniform_int_distribution<h_type> distB(0, p-1);

        a = distA(rng);
        b = distB(rng);
    }

    h_type operator()(h_type k) const {
        return (h_type) (((a*k + b) % p) % m);
    }
};

enum status {
    FIRST, SECOND, BOTH
};

typedef unordered_map<char, status> union_set;

void fill(union_set& m, const string& s, int k, status st) {
    hash<string> hashFunction;
    string shingle(k, ' ');
    for(int i = 0; i <= s.size()-k; ++i) {
        for(int j = 0; j < k; ++j) {
            shingle[j] = s[i+j];
        }
        pair<union_set::iterator, bool> result = m.insert(pair<h_type, status>(hashFunction(shingle), st));
        if(!result.second) {
            if(result.first->second != st) {
                result.first->second = BOTH;
            }
        }
    }
}

vector<Hash> generateHashes(int t, int size, int seed) {
    mt19937 rng(seed);
    uniform_int_distribution<int> dist(0, INT_MAX);
    vector<Hash> hashes(t);
    for(int i = 0; i < t; ++i) {
        hashes[i] = Hash(size, size, ((int)dist(rng)));
    }
    return hashes;
}

signatures generateSignatures(const union_set& m, const vector<Hash>& hashes) {
    signatures sigs(vector<int>(hashes.size(), -1), vector<int>(hashes.size(), -1));
    int r = 0;
    union_set::const_iterator i = m.begin();
    while(i != m.end()) {
        status st = i->second;
        for(int h = 0; h < hashes.size(); ++h) {
            int p = hashes[h](r);
            if(st == BOTH || st == FIRST) {
                if(sigs.first[h] == -1 || p < sigs.first[h]) {
                    sigs.first[h] = p;
                }
            }
            if(st == BOTH || st == SECOND) {
                if(sigs.second[h] == -1 || p < sigs.second[h]) {
                    sigs.second[h] = p;
                }
            }
        }
        ++r;
        ++i;
    }
    return sigs;
};

float computeSim(const vector<int>& sig1, const vector<int>& sig2) {
    int j = 0;
    for(int i = 0; i < sig1.size(); ++i) {
        if(sig1[i] == sig2[i]) {
            ++j;
        }
    }
    return ((float)j)/(sig1.size());
}

float computeMinhash(const string& file1, const string& file2, int k, int t, int seed) {
    union_set m;
    fill(m, file1, k, FIRST);
    fill(m, file2, k, SECOND);
    vector<Hash> hashes = generateHashes(t, m.size(), seed);
    signatures sigs = generateSignatures(m, hashes);
    return computeSim(sigs.first, sigs.second);
}