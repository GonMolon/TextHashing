#include <string>
#include <vector>
#include <stdlib.h>
#include <random>
#include <limits.h>
using namespace std;

float generateUniversalSignature(int k) {

}

float computeMinhash(string file1, string file2, int k, int t, int seed) {
    mt19937 rng(seed);
    uniform_int_distribution<int> dist(0, INT_MAX);
    dist(rng);
    return 1;
}