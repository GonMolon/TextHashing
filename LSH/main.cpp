#include <vector>
#include <string>
#include "../SimCalculator/Minhash.cpp"
using namespace std;

double computeLSH(const vector<string>& names, const vector<string*>& files, int k, int t, int seed) {
    vector<Hash> hashes = generateHashes(t, seed);
    vector<signature> m(files.size());
    for(int i = 0; i < m.size(); ++i) {
        m[i] = generateSignature(k, *(files[i]), hashes, true);
    }
    return 1;
}