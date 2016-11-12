#ifndef A_TEXTHASHING_JACCARD_HASH_ORDER
#define A_TEXTHASHING_JACCARD_HASH_ORDER

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

    double time;
    ulong memory;

public:

    Jaccard_hash_order(string nameone, string nametwo, int k) {
        if (k < 1) {
            std::cerr << "K value too small! Minimum: 1" << std::endl;
            exit(1);
        }
        ifstream fileone(nameone);
        if (fileone.fail()) {
            std::cerr << "Unable to open file " << nameone << std::endl;
            exit(1);
        }
        ifstream filetwo(nametwo);
        if (filetwo.fail()) {
            std::cerr << "Unable to open file " << nametwo << std::endl;
            exit(1);
        }

        str_one = filetostring(fileone);
        str_two = filetostring(filetwo);
        this->k = k;

        clock_t ini = clock();
        compute();
        clock_t fin = clock();
        time = double(fin - ini) / CLOCKS_PER_SEC;

        str_one.clear();
        str_two.clear();
    }

    void compute() {
        hash<string> hasher;
        int sizeone = str_one.size();
        std::set<short> setone;
        for (int i = 0; i < sizeone - k + 1; ++i) {
            setone.insert((short)hasher(str_one.substr(i, k)));
        }
        int sizetwo = str_two.size();
        std::set<short> settwo;
        for (int i = 0; i < sizetwo - k + 1; ++i) {
            settwo.insert((short)hasher(str_two.substr(i, k)));
        }

        std::set<short>::const_iterator itone = setone.begin();
        std::set<short>::const_iterator ittwo = settwo.begin();
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

    double get_time() {
        return time;
    }
};

#endif