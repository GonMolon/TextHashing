#include <stdlib.h>

typedef unsigned int uint;

class Hash {
private:
    uint m;
    uint a;
    uint b;
    uint p;

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

    Hash(uint m, uint u) {
        this->m = m;
        p = generateNextPrime(u);
        a = rand() % p;
        while(a == 0) {
            a = rand() % p;
        }
        b = rand() % p;
    }

    uint calculate(uint k) {
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