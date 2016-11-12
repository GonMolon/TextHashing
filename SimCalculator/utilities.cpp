#ifndef A_TEXTHASHING_UTILITIES
#define A_TEXTHASHING_UTILITIES

#include <fstream>
#include <string>
#include <vector>
using namespace std;

string filetostring(ifstream &file) {
    string str;
    str.assign( (std::istreambuf_iterator<char>(file) ),
                (std::istreambuf_iterator<char>()    ) );
    return str;
}

#endif