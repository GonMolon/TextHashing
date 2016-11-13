#ifndef A_TEXTHASHING_JACCARD_HASH_ROLL
#define A_TEXTHASHING_JACCARD_HASH_ROLL

//#include <bitset>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <time.h>
#include <vector>

#include "Utils.cpp"
#include "RollingHasher.cpp"

using namespace std;

class Jaccard_hash_roll {

private:
    string str_one;
    string str_two;
    int k;

    int shingles_intersection;
    int shingles_union;

    ulong memory;

public:

    Jaccard_hash_roll(string s1, string s2, int k) {
        this->str_one = s1;
        this->str_two = s2;
        this->k = k;

        compute();

        str_one.clear();
        str_two.clear();
    }

    void compute() {
        RollingHasher hasher(257, str_one.substr(0, k));
        int sizeone = str_one.size();
        std::set<uint> setone;
        setone.insert(hasher.gethash());
        //cout << str_one.substr(0, k) << ": " << bitset<64>(hasher.gethash()) << endl;
        for (int i = k; i < sizeone; ++i) {
            hasher.roll(str_one[i]);
            setone.insert(hasher.gethash());
            //cout << str_one.substr(i-k+1, k) << ": " << bitset<64>(hasher.gethash()) << endl;
        }

        //cout << "################" << endl;

        hasher.setbase(str_two.substr(0, k));
        int sizetwo = str_two.size();
        std::set<uint> settwo;
        settwo.insert(hasher.gethash());
        //cout << str_two.substr(0, k) << ": " << bitset<64>(hasher.gethash()) << endl;
        for (int i = k; i < sizetwo; ++i) {
            hasher.roll(str_two[i]);
            settwo.insert(hasher.gethash());
            //cout << str_two.substr(i-k+1, k) << ": " << bitset<64>(hasher.gethash()) << endl;
        }

        std::set<uint>::const_iterator itone = setone.begin();
        std::set<uint>::const_iterator ittwo = settwo.begin();
        shingles_intersection = 0;
        while (itone != setone.end() && ittwo != settwo.end()) {
            if ((*itone) < (*ittwo)) {
                ++itone;
            }
            else if ((*itone) > (*ittwo)) {
                ++ittwo;
            }
            else {
                ++shingles_intersection;
                ++itone;
                ++ittwo;
            }
        }

        shingles_union = setone.size() + settwo.size() - shingles_intersection;
        memory = (setone.size() + settwo.size()) * k;
    }

    double get_similarity() {
        return (double)shingles_intersection/(double)shingles_union;
    }

    double get_memory() {
        return memory;
    }
};

#endif