#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
using namespace std;

#define FILE_WORDS 5
#define TOTAL_FILES 20
#define PATTER_NAME "file"

void randomize(vector<int>& permutation) {
    for(int i = 0; i < FILE_WORDS; ++i) {
        int to = rand() % FILE_WORDS;
        int aux = permutation[i];
        permutation[i] = permutation[to];
        permutation[to] = aux;
    }
}

vector<int> generatePermutation() {
    vector<int> permutation(FILE_WORDS);
    for(int i = 0; i < FILE_WORDS; ++i) {
        permutation[i] = i;
    }
    return permutation;
}

void generateFile(string fileName, const vector<int>& permutation, const vector<string>& words) {
    ofstream file(PATTER_NAME + fileName);
    for(int i = 0; i < FILE_WORDS; ++i) {
        if(i != 0) {
            file << " ";
        }
        file << words[permutation[i]];
    }
    file.close();
}

void generateFiles(const vector<string>& words) {
    vector<int> permutation = generatePermutation();
    for(int i = 0; i < TOTAL_FILES; ++i) {
        randomize(permutation);
        generateFile(to_string(i+1) + ".txt", permutation, words);
    }
}

vector<string> readWords() {
    vector<string> words(FILE_WORDS);
    int n = FILE_WORDS;
    while(n > 0) {
        cin >> words[n-1];
        --n;
    }
    return words;
}

int main() {
    srand((uint)time(NULL)*getpid());
    vector<string> words = readWords();
    generateFiles(words);
}