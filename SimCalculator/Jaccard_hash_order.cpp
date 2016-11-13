#ifndef A_TEXTHASHING_JACCARD_HASH_ORDER_lU5rGpijs5
#define A_TEXTHASHING_JACCARD_HASH_ORDER_lU5rGpijs5

#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <time.h>
#include <vector>
#include "Utils.cpp"

using namespace std;

class Jaccard_hash_order {

private:
    string str_one;
    string str_two;
    int k;

    int shingles_intersection;
    int shingles_union;

    ulong memory;

public:

    Jaccard_hash_order(string s1, string s2, int k) {
        this->str_one = s1;
        this->str_two = s2;
        this->k = k;

        compute();

        str_one.clear();
        str_two.clear();
    }

    void compute() {
        hash<string> hasher;
        int sizeone = str_one.size();
        std::set<uint> setone;
        for (int i = 0; i < sizeone - k + 1; ++i) {
            setone.insert((uint)hasher(str_one.substr(i, k)));
        }
        int sizetwo = str_two.size();
        std::set<uint> settwo;
        for (int i = 0; i < sizetwo - k + 1; ++i) {
            settwo.insert((uint)hasher(str_two.substr(i, k)));
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