#ifndef A_TEXTHASHING_MINHASH_NORM
#define A_TEXTHASHING_MINHASH_NORM

#include <string>
#include <vector>
#include <stdlib.h>
#include <random>
#include <limits.h>
#include <unordered_map>
#include "Utils.cpp"
using namespace std;

typedef unsigned int h_type;
typedef vector<int> signature;
typedef pair<signature, signature> signatures;

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

    void print() {
        cout << "a = " << a << endl;
        cout << "b = " << b << endl;
        cout << "p = " << p << endl;
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

signature generateSignature(int k, const string& file, const vector<Hash>& hashes) {
    signature s(hashes.size(), -1);
    hash<string> hashFunction;
    string shingle(k, ' ');
    for(int i = 0; i <= file.size()-k; ++i) {
        for(int j = 0; j < k; ++j) {
            shingle[j] = file[i+j];
        }
        int value = hashFunction(shingle);
        for(int h = 0; h < hashes.size(); ++h) {
            int p = hashes[h](value);
            if(s[h] == -1 || p < s[h]) {
                s[h] = p;
            }
        }
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
    return ((double)j)/(sig1.size());
}

double computeMinhash(const string& file1, const string& file2, int k, int t, int seed) {
    vector<Hash> hashes = generateHashes(t, seed);
    signature s1 = generateSignature(k, file1, hashes);
    signature s2 = generateSignature(k, file2, hashes);
    return computeSim(s1, s2);
}

#endif