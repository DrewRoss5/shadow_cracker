#ifndef WORDLIST_ATTACK_H
#define WORDLIST_ATTACK_H

#include "attack.hpp"

class WordlistCracker : public AttackType{
    public:
        WordlistCracker(const std::string& candidate_file);
        std::string run_attack(const std::string& checksum, bool multithread) override;
    private:
        std::string result;
        std::vector<std::string> candidates;
        void scan_singlethread(const std::string& checksum);
        void scan_multithread(const std::string& checksum);
};


#endif