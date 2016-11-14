#ifndef A_TEXTHASHING_UTILITIES_lU5rGpijs5
#define A_TEXTHASHING_UTILITIES_lU5rGpijs5

#include <fstream>
#include <iostream>

using namespace std;

namespace utils {

    string file_to_string(ifstream &file) {
        string str;
        str.assign((std::istreambuf_iterator<char>(file)),
                   (std::istreambuf_iterator<char>()));
        return str;
    }

    uint pow_mod(long a, long b, long mod) {
        if (b == 0) {
            return 1;
        }
        if (b == 1) {
            return a % mod;
        }
        long powa = pow_mod(a, b/2, mod);
        powa = powa*powa;
        if (b & 1) {
            powa = powa*a;
        }
        return powa % mod;
    }

    string getFileName(const string& path) {
        int k = -1;
        bool found = false;
        for(int i = path.size()-1; !found && i >= 0; --i) {
            if(path[i] == '/') {
                k = i;
                found = true;
            }
        }
        if(k == -1) {
            return "";
        } else {
            string s(path.size()-k-1, ' ');
            ++k;
            for(int i = 0; i < s.size(); ++i) {
                s[i] = path[k];
                ++k;
            }
            return s;
        }
    }
}

std::ostream& bold_on(std::ostream& os) {
    return os << "\e[1m";
}

std::ostream& bold_off(std::ostream& os) {
    return os << "\e[0m";
}

std::ostream& uline_on(std::ostream& os) {
    return os << "\e[4m";
}

std::ostream& uline_off(std::ostream& os) {
    return os << "\e[0m";
}

#endif