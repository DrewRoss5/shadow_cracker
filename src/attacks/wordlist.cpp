#include <fstream>
#include <stdexcept>

#include "../../inc/attacks/wordlist.hpp"

// this function simply reads all candidate passwords in a given file and 
std::vector<std::string> parse_candidate_file(const std::string& file_path){
    // open the file
    std::ifstream candidate_file(file_path);
    if (!candidate_file.good())
        throw std::runtime_error("Failed to read the candidate file. Does it exist?");
    // read line to the output vector
    std::vector<std::string> candidates;
    std::string tmp;
    while (std::getline(candidate_file, tmp))
        candidates.push_back(tmp);
    candidate_file.close();
    return candidates;
}