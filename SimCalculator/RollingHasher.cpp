#ifndef A_ROLLINGHASHER
#define A_ROLLINGHASHER

//#include <bitset>
#include <string>
#include <queue>

#include "Utils.cpp"

using namespace std;

class RollingHasher {

private:
    const ulong prime;
    queue<char> next_out;
    long prime_powered;
    long hashval;

public:
    RollingHasher(uint prime, const string &base_str) :
            prime((long)prime)
    {
        setbase(base_str);
    }

    void setbase(const string &base_str) {
        while (!next_out.empty()) {
            next_out.pop();
        }
        hashval = 0;
        prime_powered = utils::pow_mod(prime, base_str.size() - 1, 4294967296);
        for (int i = 0; i < base_str.size(); ++i) {
            hashval = ((hashval * prime) + base_str[i]) % 4294967296;
            next_out.push(base_str[i]);
        }
    }

    void roll(char c) {
        next_out.push(c);
        hashval = (hashval - next_out.front()*prime_powered);
        hashval = ((hashval * prime) + c) % 4294967296;
        next_out.pop();
    }

    uint gethash() {
        return hashval;
    }

};
#endif