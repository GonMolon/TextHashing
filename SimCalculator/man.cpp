#ifndef A_MAN_lU5rGpijs5
#define A_MAN_lU5rGpijs5

#include <iostream>

void man() {
    cout << endl;
    cout << bold_on << "NAME" << bold_off << endl;
    cout << "    " << "SimCalculator" << endl;
    cout << endl;
    cout << bold_on << "USAGE" << bold_off << endl;
    cout << "    " << "SimCalculator FILE_ONE FILE_TWO " << bold_on << "MODE [PARAMETERS...]" << bold_off << endl;
    cout << endl;
    cout << "    " << "SimCalculator calculates the similarity between two text files FILE_ONE and FILE_TWO"<< endl;
    cout << "    " << "and outputs it as a number between 0 and 1, where 1 means the two files are exactly"<< endl;
    cout << "    " << "the same."<< endl;
    cout << endl;
    cout << bold_on << "MODE" << bold_off << endl;
    cout << "    " << "There are five different modes which change the way SimCalculator computes the simi-" << endl;
    cout << "    " << "larity. Each may make use of different parameters, indicated as follows:"<< endl;;
    cout << endl;
    cout << "    " << bold_on << "all" << bold_off << endl;
    cout << "        " << "This option executes all modes." << endl;
    cout << endl;
    cout << "    " << bold_on << "jaccard" << bold_off << endl;
    cout << "        " << "Performs the calculation by storing k-shingles as strings in a set for each file."<< endl;
    cout << "        " << "Used parameters are: " << endl;
    cout << endl;
    cout << "            " << "--k=POSITIVE_INTEGER as shingle size"<< endl;
    cout << endl;
    cout << "    " << bold_on << "jaccard_hash" << bold_off << endl;
    cout << "        " << "Performs the calculation by storing k-shingles as 4-byte hashes in a set for each"<< endl;
    cout << "        " << "file. Uses less memory than jaccard, at the expense of a possible loss in" << endl;
    cout << "        " << "precision for large values of k. Used parameters are:"<< endl;
    cout << endl;
    cout << "            " << "--k=POSITIVE_INTEGER as shingle size"<< endl;
    cout << endl;
    cout << "    " << bold_on << "jaccard_roll" << bold_off << endl;
    cout << "        " << "Same as jaccard_hash, but hashes k-shingles by using a rolling hash. Better time"<< endl;
    cout << "        " << "performance than jaccard_hash for greater values of k. Used parameters are:" << endl;
    cout << endl;
    cout << "            " << "--k=POSITIVE_INTEGER as shingle size"<< endl;
    cout << endl;
    cout << "    " << bold_on << "minhash" << bold_off << endl;
    cout << "        " << "Calculates the similarity by computing minhash signatures for each document. Used"<< endl;
    cout << "        " << "parameters are."<< endl;
    cout << endl;
    cout << "            " << "--k=POSITIVE_INTEGER as shingle size"<< endl;
    cout << endl;
    cout << "            " << "--t=POSITIVE_INTEGER as number of hash functions used"<< endl;
    cout << endl;
    cout << "            " << "--seed=INTEGER as random generator seed"<< endl;
    cout << endl;
    cout << "    " << bold_on << "minhash_roll" << bold_off << endl;
    cout << "        " << "Same as minhash mode, but uses a rolling hash. Better time performace tha minhash"<< endl;
    cout << "        " << "for greater values of k. Used parameters are:"<< endl;
    cout << endl;
    cout << "            " << "--k=POSITIVE_INTEGER as shingle size"<< endl;
    cout << endl;
    cout << "            " << "--t=POSITIVE_INTEGER as number of hash functions used"<< endl;
    cout << endl;
    cout << "            " << "--seed=INTEGER as random generator seed"<< endl;
    cout << endl;
    cout << bold_on << "PARAMETERS" << bold_off << endl;
    cout << endl;
    cout << "    " << bold_on << "--k=POSITIVE_INTEGER" << bold_off << endl;
    cout << "        " << "Defaults to k=9. Indicates the size of the shingles used to calculate the simi-"<< endl;
    cout << "        " << "larity between the documents."<< endl;
    cout << endl;
    cout << "    " << bold_on << "--t=POSITIVE_INTEGER" << bold_off << endl;
    cout << "        " << "Defaults to t=5. Indicates the number of hash functions used in minhash modes."<< endl;
    cout << endl;
    cout << "    " << bold_on << "--seed=INTEGER" << bold_off << endl;
    cout << "        " << "Defaults to a random value. Used by minhash modes in their random generator number."<< endl;
    cout << endl;
    cout << "    " << bold_on << "-e" << bold_off << endl;
    cout << "        " << "Output in experimentation format."<< endl;
    cout << endl;
    exit(0);
}

#endif