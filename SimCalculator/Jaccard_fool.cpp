#include <fstream>
#include <iostream>
#include <set>
#include <vector>
using namespace std;

std::string filetostring(std::ifstream &file) {
    std::string str;
    str.assign( (std::istreambuf_iterator<char>(file) ),
                (std::istreambuf_iterator<char>()    ) );
    return str;
}

class Jaccard_fool {

private:
    string str_one;
    string str_two;
    int shingles_intersection;
    int shingles_union;
    int k;

public:

    Jaccard_fool(string nameone, string nametwo, int k) {
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

        compute();

        str_one.clear();
        str_two.clear();
    }

    void compute() {
        int sizeone = str_one.size();
        std::set<std::string> setone;
        for (int i = 0; i < sizeone - k + 1; ++i) {
            setone.insert(str_one.substr(i, k));
        }
        int sizetwo = str_two.size();
        std::set<std::string> settwo;
        for (int i = 0; i < sizetwo - k + 1; ++i) {
            settwo.insert(str_two.substr(i, k));
        }

        std::set<std::string>::const_iterator itone = setone.begin();
        std::set<std::string>::const_iterator ittwo = settwo.begin();
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
    }

    double get_similarity() {
        return (double)shingles_union/(double)shingles_intersection;
    }

};