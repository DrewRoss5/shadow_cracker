#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <fstream>
#include <crypt.h>

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

// parses all username and password combinations from a shadow file, and strips off unnecessary metadata from the password entries
std::unordered_map<std::string, std::string> parse_shadow(std::string shadow_path){
    // open the file
    std::ifstream shadow_file(shadow_path);
    if (!shadow_file.good())
        throw std::runtime_error("Cannot read the shadow file. Does it exist?");
    // read the file and parse each line
    std::string curr_line, username, pw_hash;
    std::vector<std::string> segments;
    std::unordered_map<std::string, std::string> out;
    while (std::getline(shadow_file, curr_line)){
        segments = split_str(curr_line, ':');
        if (segments.size() < 2)
            throw std::runtime_error("Invalid shadow file format");
        username = segments[0];
        pw_hash = segments[1];
        out[username] = pw_hash;
    }
    shadow_file.close();
    return out;
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