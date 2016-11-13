#ifndef A_ROLLINGHASHER
#define A_ROLLINGHASHER

#include "Utils.cpp"
#include <string>
#include <queue>
using namespace std;

class RollingHasher {

private:
    const ulong prime_pro;
    queue<char> next_out;
    ulong prime_powered;
    ulong hashval;

public:
    RollingHasher(ulong prime, const string &base) :
            prime_pro(prime)
    {
        setbase(base);
    }

    void setbase(const string &base) {
        while (!next_out.empty()) {
            next_out.pop();
        }
        hashval = 0;
        prime_powered = 1;
        for (int i = 0; i < base.size(); ++i) {
            ulong charval = (ulong)base[i];
            hashval = (hashval + charval * prime_powered);
            hashval = hashval & 4294967295;
            prime_powered = prime_powered*prime_pro;
            prime_powered = prime_powered & 4294967295;
            next_out.push(base[i]);
        }
    }

    void roll(char c) {
        ulong out = (ulong)next_out.front();
        next_out.push(c);
        next_out.pop();
        hashval = hashval - out;
        hashval = hashval / prime_pro;
        hashval = hashval + (ulong)c * prime_pro;
        hashval = hashval & 4294967295;
    }

    uint gethash() {
        return hashval;
    }

};
#endif