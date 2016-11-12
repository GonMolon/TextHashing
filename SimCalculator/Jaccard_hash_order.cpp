#ifndef A_TEXTHASHING_JACCARD_HASH_ORDER
#define A_TEXTHASHING_JACCARD_HASH_ORDER

#include <algorithm>
#include <string>
#include "utilities.cpp"
#include <vector>
using namespace std;

class Jaccard_hash_order {

private:


public:

};

float computeJaccard(vector<string>& shingles1, vector<string>& shingles2) {
    vector<int> common_data, union_data;

    vector<int> h_shingles1(shingles1.size());
    vector<int> h_shingles2(shingles2.size());
    hash<string> str_hash;

    for(int i = 0; i < shingles1.size(); ++i) {
        h_shingles1[i] = str_hash(shingles1[i]);
    }
    for(int i = 0; i < shingles2.size(); ++i) {
        h_shingles2[i] = str_hash(shingles2[i]);
    }

    sort(h_shingles1.begin(), h_shingles1.end());
    sort(h_shingles2.begin(), h_shingles2.end());

    set_intersection(h_shingles1.begin(), h_shingles1.end(), h_shingles2.begin(), h_shingles2.end(), std::inserter(common_data, common_data.begin()));

    set_union(h_shingles1.begin(), h_shingles1.end(), h_shingles2.begin(), h_shingles2.end(), std::inserter(union_data, union_data.begin()));

    return float(common_data.size())/float(union_data.size());
}

#endif