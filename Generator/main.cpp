#include <algorithm>
#include <fstream>
#include <iostream>
#include <stdlib.h> //exit()
#include <random>
#include <vector>

int count_words(std::ifstream &inp) {
    int count = 0;
    std::string word;
    while (inp >> word) {
        ++count;
    }
    inp.clear();
    inp.seekg(0, std::ios::beg);
    return count;
}

std::vector<std::string> filetovec(std::ifstream &file) {
    std::size_t n = (std::size_t)count_words(file);
    std::vector<std::string> input_words(n);
    for (int i = 0; i < n; ++i) {
        file >> input_words[i];
    }
    file.clear();
    file.seekg(0, std::ios::beg);
    return input_words;
}

void vectofile(std::ofstream &file, const std::vector<std::string> &vec) {
    int n = (int)vec.size();
    if (n > 0) {
        file << vec[0];
        for (int i = 1; i < n; ++i) {
            file << " " << vec[i];
        }
    }
    file << std::endl;
    file.clear();
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "usage: %s INPUT_FILE OUTPUT_FILE\n", argv[0]);
        exit(1);
    }
    std::ifstream inp(argv[1]);
    if (inp.fail()) {
        fprintf(stderr, "Unable to open input file %s\n", argv[1]);
        exit(1);
    }
    std::ofstream out(argv[2]);
    if (out.fail()) {
        fprintf(stderr, "Unable to open output file %s\n", argv[1]);
        exit(1);
    }

    std::vector<std::string> input_words = filetovec(inp);

    std::random_device rd;
    std::mt19937 rng(rd());
    std::shuffle(input_words.begin(), input_words.end(), rng);

    vectofile(out, input_words);
}