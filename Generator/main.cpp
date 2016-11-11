#include <algorithm>
#include <fstream>
#include <iostream>
#include <stdlib.h> //exit()
#include <random>
#include <vector>

void usage(const std::string &filename) {
    std::cerr << "usage: " << filename << " INPUT_FILE OUTPUT_FILE [-w WORDS_PER_LINE] [-s RNG_SEED]\n";
    exit(1);
}

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

void vectofile(std::ofstream &file, const std::vector<std::string> &vec, int wperline) {
    int n = (int)vec.size();
    if (n > 0) {
        for (int i = 0; i < n; ++i) {
            file << vec[i];
            for (int w = 1; w < wperline && i < n;) {
                file << " " << vec[i];
                ++i;
                ++w;
            }
            file << std::endl;
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        usage(std::string(argv[0]));
    }

    std::string words_per_line, rng_seed;
    for (int i = 3; i < argc; ++i) {
        std::string option(argv[i]);
        if (option == "-w") {
            ++i;
            if (i < argc) {
                words_per_line = std::string(argv[i]);
            }
        }
        else if (option == "-s") {
            ++i;
            if (i < argc) {
                rng_seed = std::string(argv[i]);
            }
        }
    }

    std::ifstream inp(argv[1]);
    if (inp.fail()) {
        std::cerr << "Unable to open input file " << argv[1] << std::endl;
        exit(1);
    }
    std::ofstream out(argv[2]);
    if (out.fail()) {
        std::cerr << "Unable to open input file " << argv[1] << std::endl;
        exit(1);
    }

    // Read file
    std::vector<std::string> input_words = filetovec(inp);

    // Random shuffle
    std::mt19937 rng;
    if (rng_seed != "") {
        rng.seed(std::stoul(rng_seed));
    }
    else {
        std::random_device rd;
        rng.seed(rd());
    }
    std::shuffle(input_words.begin(), input_words.end(), rng);

    // Output to file
    int wperline = (int)input_words.size();
    if (words_per_line != "") {
        int w = std::stoi(words_per_line);
        if (w > 0) {
            wperline = w;
        }
    }
    vectofile(out, input_words, wperline);
}