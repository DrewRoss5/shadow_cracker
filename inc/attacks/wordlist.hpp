#ifndef WORDLIST_ATTACK_H
#define WORDLIST_ATTACK_H

#include "attack.hpp"

class WordlistCracker : public AttackType{
    public:
        WordlistCracker(std::string candidate_file);
        std::string run_attack(const std::string& checksum, bool multithread) override;
    private:
        std::vector<std::string> candidates;
};


#endif