#ifndef CRACKER_UTILS_H
#define CRACKER_UTILS_H

#include <vector>
#include <string>
#include <unordered_map>

void print_err(const std::string& err_msg);
std::vector<std::string> split_str(const std::string& input, char delim);
std::unordered_map<std::string, std::string> parse_shadow(std::string shadow_path);
bool check_pass(const std::string& candidate, const std::string& checksum);

#endif