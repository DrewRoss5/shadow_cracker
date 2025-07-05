#include <fstream>
#include <iostream>
#include <thread>

#include "../../inc/attacks/wordlist.hpp"
#include "../../inc/utils.hpp"

WordlistCracker::WordlistCracker(const std::string& candidate_path){
    this->result = "";
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
void WordlistCracker::scan_multithread(const std::string& checksum){
    size_t thread_count = std::thread::hardware_concurrency();
    size_t candidate_count = this->candidates.size();
    size_t segment_size = candidate_count / thread_count;
    // spawn all threads to find a match
    std::vector<std::thread> threads;
    for (int i = 0; i < thread_count - 1; i++)
        threads.push_back(std::thread(&WordlistCracker::scan_singlethread, this, checksum, segment_size * i, segment_size * (i + 1)));
    // we add the last thread seprately to account for thread_count possibly being rounded down
    threads.push_back(std::thread(&WordlistCracker::scan_singlethread, this, checksum, segment_size * (thread_count - 1), candidate_count));
    // kill all threads
    for (int i = 0; i < thread_count; i++)
        threads[i].join();
}

// checks every candidate against the checksum, stopping if the result is found, uses one thread
void WordlistCracker::scan_singlethread(const std::string& checksum, size_t start, size_t end){
    if (!end)
        end = this->candidates.size();
    for (size_t i = start; i < end; i++){
        if (check_pass(candidates[i], checksum)){
            this->result = candidates[i];
            return;
        }
    }
}