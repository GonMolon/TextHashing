#ifndef A_ROLLINGHASHER
#define A_ROLLINGHASHER

#include "Utils.cpp"
#include <string>
#include <queue>
using namespace std;

class RollingHasher {

private:
    const uint prime_pro;
    const uint prime_mod;
    queue<char> next_out;
    uint prime_powered;
    uint hashval;

public:
    RollingHasher(uint prime, const string &base) :
            prime_pro(prime_pro),
            prime_mod(prime_mod)
    {
        setbase(base);
    }

    void setbase(const string &base) {
        while (!next_out.empty()) {
            next_out.pop();
        }
        hashval = 0;
        prime_powered = 1;
        string::const_iterator ch = base.begin();
        while (ch != base.end()) {
            hashval = (short)(hashval + ((*ch) * prime_powered));
            prime_powered = (short)(prime_powered * prime_pro);
            next_out.push(*ch);
            ++ch;
        }
    }

    void roll(char c) {
        next_out.push(c);
        char out = next_out.front();
        hashval = (short)((hashval - out) / prime_pro + c * prime_powered);
        next_out.pop();
    }

    short gethash() {
        return hashval;
    }

};
#endif