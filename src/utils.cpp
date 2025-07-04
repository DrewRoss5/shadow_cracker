#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <fstream>
#include <unistd.h>
#include <crypt.h>
#include <algorithm>

#include "../inc/utils.hpp"

#define CRYPT_OUT_SIZE 128

// prints an error with a specified message
void print_err(const std::string& err_msg){
    std::cout << "\033[31mError:\033[0m " << err_msg << std::endl;
}

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
        // remove new line and carriage return
        auto new_end = std::remove(pw_hash.begin(), pw_hash.end(), '\r');
        pw_hash.erase(new_end, pw_hash.end());
        out[username] = pw_hash;
    }
    shadow_file.close();
    return out;
}

// gets just the salt from a password hash
std::string get_hash_salt(const std::string& pw_hash){
    std::vector<std::string> segments = split_str(pw_hash, '$');
    return "$" + segments[1] + "$" + segments[2] + "$";
}

// checks a password checksum against a candidate password and returns true if the checksum matches, otherwise returns false
bool check_pass(const std::string& candidate, const std::string& checksum){
    crypt_data out;
    out.initialized = 0;
    std::string salt = get_hash_salt(checksum);
    crypt_r(candidate.c_str(), salt.c_str(), &out); // hashes candidate using checksum as salt
    std::string hashed_candidate = out.output;
    if (!out.output)
        throw std::runtime_error("Failed to hash candidate: " + hashed_candidate);
    return hashed_candidate == checksum;
}