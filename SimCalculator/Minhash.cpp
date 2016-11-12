#include <string>
#include <vector>
#include <stdlib.h>
#include <random>
#include <limits.h>
#include <map>
#include "Utils.cpp"
using namespace std;

typedef unsigned int h_type;

class Hash {
private:
    h_type m;
    h_type a;
    h_type b;
    long p;

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
            n += n;
        }
        return n;
    }

public:

    Hash(){}

    Hash(h_type m, h_type u, int seed) {
        this->m = m;
        p = generateNextPrime(u);

        mt19937 rng(seed);
        uniform_int_distribution<h_type> dist(0, p-1);

        a = dist(rng);
        while(a == 0) {
            a = dist(rng);
        }
        b = dist(rng);
    }

    h_type operator()(h_type k) {
        return (h_type) (((a*k + b) % p) % m);
    }
};

enum status {
    FIRST, SECOND, BOTH
};

typedef map<short, status> union_set;

void fill(union_set& m, const string& s, int k, status st) {
    hash<string> hashFunction;
    string shingle(k, ' ');
    for(int i = 0; i < s.size()-k; ++i) {
        for(int j = 0; j < k; ++j) {
            shingle[j] = s[i+j];
        }
        pair<union_set::iterator , bool> result = m.insert(pair<short, status>((short)hashFunction(shingle), st));
        if(!result.second) {
            result.first->second = BOTH;
        }
    }
}

float generateUniversalSignature(int k) {

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

float computeMinhash(const string& file1, const string& file2, int k, int t, int seed) {
    union_set m;
    fill(m, file1, k, FIRST);
    fill(m, file2, k, SECOND);
    vector<Hash> hashes = generateHashes(t, m.size(), seed);
    return 1;
}