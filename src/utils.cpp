#include <iostream>
#include <vector>
#include <string>
#include <crypt.h>
#include <stdexcept>


#include "../inc/utils.hpp"

#define CRYPT_OUT_SIZE 128



// splits a string into segments, seperated by a delimiter
std::vector<std::string> split_str(const std::string& input, char delim){
    std::vector<std::string> segments;
    int start_pos {0}, delim_pos = 0;
    std::string tmp;
    while (delim_pos != std::string::npos){
      delim_pos = input.find(delim, start_pos);
      tmp = input.substr(start_pos, delim_pos - start_pos);
      segments.push_back(tmp);
      start_pos = delim_pos + 1;
    }
    return segments;
}

// checks a password checksum against a candidate password and returns true if the checksum matches, otherwise returns false
bool check_pass(const std::string& candidate, const std::string& checksum){
    crypt_data out;
    out.initialized = 0;
    crypt_r(candidate.c_str(), checksum.c_str(), &out);
    if (!out.output)
        throw std::runtime_error("Failed to hash candidate: " + candidate);
    return out.output == checksum;
}