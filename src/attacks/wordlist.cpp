#include <fstream>
#include <iostream>

#include "../../inc/attacks/wordlist.hpp"
#include "../../inc/utils.hpp"

WordlistCracker::WordlistCracker(const std::string& candidate_path){
    // ensure the candidate file exists
    std::ifstream candidate_file(candidate_path);
    if (!candidate_file.good())
        throw std::runtime_error("Could not read the candidate file. Does it exist?");
    // read all the candidate passwords
    std::string tmp;
    while (std::getline(candidate_file, tmp))
        this->candidates.push_back(tmp);
    candidate_file.close();
}

// calls either the single- or multithreaded attack, and returns the result
std::string WordlistCracker::run_attack(const std::string& checksum, bool multithread){
    if (multithread)
        scan_multithread(checksum);
    else
        scan_singlethread(checksum);
    return this->result;
}

// checks every candidate against the checksum, stopping if the result is found, will use all available threads
// !UNIMPLEMNTED!
void WordlistCracker::scan_multithread(const std::string& checksum){
    throw std::runtime_error("Multithreading for wordlist scans is not yet implemented.");
}

// checks every candidate against the checksum, stopping if the result is found, uses one thread
void WordlistCracker::scan_singlethread(const std::string& checksum){
    size_t candidate_size = this->candidates.size();
    for (size_t i = 0; i < candidate_size; i++){
        if (check_pass(candidates[i], checksum)){
            result = candidates[i];
            return;
        }
    }
    result = "";
}