#ifndef A_TEXTHASHING_UTILITIES
#define A_TEXTHASHING_UTILITIES

#include <fstream>
using namespace std;

namespace utils {

    string file_to_string(ifstream &file) {
        string str;
        str.assign((std::istreambuf_iterator<char>(file)),
                   (std::istreambuf_iterator<char>()));
        return str;
    }

    uint pow_mod(uint a, uint b, uint mod) {
        if (b == 0) {
            return 1;
        }
        if (b == 1) {
            return a % mod;
        }
        uint powa = pow_mod(a, b/2, mod);
        powa = powa*powa;
        if (b & 1) {
            powa = powa*a;
        }
        return powa % mod;
    }
}

#endif