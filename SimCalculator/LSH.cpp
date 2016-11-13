#ifndef A_TEXTHASHING_LSH_lU5rGpijs5
#define A_TEXTHASHING_LSH_lU5rGpijs5

#include <vector>
#include <string>
#include "Minhash_norm.cpp"
using namespace std;

double computeLSH(const vector<string>& names, const vector<string*>& files, int k, int t, int seed) {
    vector<Hash> hashes = generateHashes(t, seed);
    vector<signature> m(files.size());
    for(int i = 0; i < m.size(); ++i) {
        m[i] = generateSignature(k, *(files[i]), hashes);
    }
    return 1;
}

#endif