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

std::string scan_singlethread(const std::string checksum, const std::vector<std::string>& candidates){
    std::string result = "";
    return result;
}

std::string scan_multithread(const std::string checksum, const std::vector<std::string>& candidates){
    std::string result = "";
    return result;
}

// performs a scan of a password database, returns the password fro the provided user if found, otherwise returns an emptty string
std::string wordlist_scan(const std::unordered_map<std::string, std::string>& password_db,  const std::string& candidate_file, const std::string& target, bool multithread = false){
    // ensure there is a checksum for the provdied username
    auto tmp = password_db.find(target);
    if (tmp == password_db.end())
        throw std::runtime_error("User " + target + " not found.");
    std::string checksum  = tmp->second;
    // open the candidate file
    std::vector<std::string> candidates = parse_candidate_file(candidate_file);
    // run the scan
    if (multithread)
        return scan_multithread(checksum, candidates);
    else 
        return scan_singlethread(checksum, candidates);

}