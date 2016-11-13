#ifndef A_TEXTHASHING_MINHASH_NORM
#define A_TEXTHASHING_MINHASH_NORM

#include <string>
#include <vector>
#include <stdlib.h>
#include <random>
#include <limits.h>
#include <unordered_set>
#include "Utils.cpp"
#include "RollingHasher.cpp"
using namespace std;

typedef unsigned int h_type;
typedef vector<int> signature;

class Hash {
private:
    h_type m;
    long a;
    long b;
    long p;

    bool is_prime(long x) {
        long i = 3;
        while(true) {
            long q = x/i;
            if(q < i) {
                return true;
            }
            if(x == q * i) {
                return false;
            }
            i += 2;
        }
    }

    long generateNextPrime(long n) {
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

vector<Hash> generateHashes(int t, int seed) {
    mt19937 rng(seed);
    uniform_int_distribution<int> dist(0, INT_MAX);
    vector<Hash> hashes(t);
    for(int i = 0; i < t; ++i) {
        hashes[i] = Hash(INT_MAX, INT_MAX, ((int)dist(rng)));
    }
    return hashes;
}

void insertValue(int value, signature& s, unordered_set<int>& filter, const vector<Hash>& hashes) {
    if(filter.insert(value).second) {
        for(int h = 0; h < hashes.size(); ++h) {
            int p = hashes[h](value);
            if(s[h] == -1 || p < s[h]) {
                s[h] = p;
            }
        }
    }
}

signature generateSignature(int k, const string& file, const vector<Hash>& hashes, bool rollingHash) {
    signature s(hashes.size(), -1);
    unordered_set<int> filter;
    if(!rollingHash) {
        hash<string> hashFunction;
        string shingle(k, ' ');
        for(int i = 0; i <= file.size()-k; ++i) {
            for(int j = 0; j < k; ++j) {
                shingle[j] = file[i+j];
            }
            insertValue(hashFunction(shingle), s, filter, hashes);
        }
    } else if(k <= file.size()) {
        string shingle = file.substr(0, k);
        RollingHasher hasher(257, shingle);
        for(int i = k; i < file.size(); ++i) {
            insertValue(hasher.gethash(), s, filter, hashes);
            hasher.roll(file[i]);
        }
        insertValue(hasher.gethash(), s, filter, hashes);
    }
    return s;
}

double computeSim(const vector<int>& sig1, const vector<int>& sig2) {
    int j = 0;
    for(int i = 0; i < sig1.size(); ++i) {
        if(sig1[i] == sig2[i]) {
            ++j;
        }
    }
    return double(j)/double(sig1.size());
}

double computeMinhash(const string& file1, const string& file2, int k, int t, int seed, bool rollingHash) {
    vector<Hash> hashes = generateHashes(t, seed);
    signature s1 = generateSignature(k, file1, hashes, rollingHash);
    signature s2 = generateSignature(k, file2, hashes, rollingHash);
    return computeSim(s1, s2);
}

#endif