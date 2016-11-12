#ifndef A_TEXTHASHING_UTILITIES
#define A_TEXTHASHING_UTILITIES

#include <fstream>
#include <random>
using namespace std;

typedef unsigned int uint;

string filetostring(ifstream &file) {
    string str;
    str.assign( (std::istreambuf_iterator<char>(file) ),
                (std::istreambuf_iterator<char>()    ) );
    return str;
}


class Hash {
private:
    uint m;
    uint a;
    uint b;
    uint p;
    mt19937 rng;

    bool is_prime(uint x) {
        uint i = 3;
        while(true) {
            uint q = x/i;
            if(q < i) {
                return true;
            }
            if(x == q * i) {
                return false;
            }
            i += 2;
        }
    }

    uint generateNextPrime(uint n) {
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

    Hash(uint m, uint u, int seed) {
        this->m = m;
        p = generateNextPrime(u);

        mt19937 rng(seed);
        uniform_int_distribution<uint> dist(0, p-1);

        a = dist(rng);
        while(a == 0) {
            a = dist(rng);
        }
        b = dist(rng);
    }

    uint operator()(uint k) {
        return ((a*k + b) % p) % m;
    }
};

/*
MAGI:

void readFile(std::ifstream& in, std::string& string, int streamsize) {
    int pos=0;
    while(pos < streamsize){
        in.get(string[pos]);
        ++pos;
    }
}

// Params:(name of document, queue for shingles (maybe better other structure), k)

vector<string> file_shingling(string file, int k) {
    vector<string> shingles;
    set<string> control;
    ifstream fIn(file, ios::in);
    string shingle;
    shingle.resize(k);
    int charPos = 1;
    while(!fIn.eof()) {

        readFile(fIn, shingle, k);

        if(control.find(shingle) == control.end()) {
            shingles.push_back(shingle);
            control.insert(shingle);
        }

        if(fIn.peek() == '\n') ++charPos;
        if(fIn.eof()) return shingles;
        fIn.seekg(charPos++);

    }
    return shingles;
}
 */

#endif