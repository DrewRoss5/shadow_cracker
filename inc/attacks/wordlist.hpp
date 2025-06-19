#ifndef ATTACK_WORDLIST
#define ATTACK_WORDLIST

#include <vector>
#include <string>
#include <unordered_map>

std::vector<std::string> parse_candidate_file(const std::string& file_path);
std::string wordlist_scan(const std::unordered_map<std::string, std::string>& password_db,  std::string& candidate_file, std::string target, bool multithread = false);


#endif