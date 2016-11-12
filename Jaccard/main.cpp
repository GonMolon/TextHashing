#include <fstream>
#include <iostream>
#include <set>
#include <vector>

void usage(const std::string &filename) {
    std::cerr << "JACCARD usage:\n";
    std::cerr << "\t$" << filename << " FILE_ONE FILE_TWO K\n";
    std::cerr << "~~~~~~~~~~~~~~~~\n";
    exit(1);
}

std::string filetostring(std::ifstream &file) {
    std::string str;
    str.assign( (std::istreambuf_iterator<char>(file) ),
                (std::istreambuf_iterator<char>()    ) );
    return str;
}

double computeJaccard(const std::string &stringone, const std::string &stringtwo, int k) {
    int sizeone = stringone.size();
    std::set<std::string> setone;
    for (int i = 0; i < sizeone - k + 1; ++i) {
        setone.insert(stringone.substr(i, k));
    }
    int sizetwo = stringone.size();
    std::set<std::string> settwo;
    for (int i = 0; i < sizetwo - k + 1; ++i) {
        settwo.insert(stringtwo.substr(i, k));
    }

    std::set<std::string>::const_iterator itone = setone.begin();
    std::set<std::string>::const_iterator ittwo = settwo.begin();
    int count_collisions = 0;
    while (itone != setone.end() && ittwo != settwo.end()) {
        if ((*itone) < (*ittwo)) {
            ++itone;
        }
        else if ((*itone) > (*ittwo)) {
            ++ittwo;
        }
        else {
            ++count_collisions;
            ++itone;
            ++ittwo;
        }
    }

    return ((double)count_collisions)/((double)(setone.size() + settwo.size() - count_collisions));
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        usage(std::string(argv[0]));
    }
    std::ifstream fileone(argv[1]);
    if (fileone.fail()) {
        std::cerr << "Unable to open file " << argv[1] << std::endl;
        exit(1);
    }
    std::ifstream filetwo(argv[2]);
    if (filetwo.fail()) {
        std::cerr << "Unable to open file " << argv[2] << std::endl;
        exit(1);
    }
    int k = std::stoi(std::string(argv[3]));
    if (k < 1) {
        std::cerr << "K argument is too small! (Minimum: 1, Read: " << k << ")" << std::endl;
        exit(1);
    }

    std::string stringone = filetostring(fileone);
    std::string stringtwo = filetostring(filetwo);

    std::cout << "ONE: " << stringone << std::endl;
    std::cout << "TWO: " << stringtwo << std::endl;

    // time start
    double jaccard_sim = computeJaccard(stringone, stringtwo, k);
    // time stop

    std::cout << k << jaccard_sim /*<< time */<< std::endl;
}