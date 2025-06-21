#include <iostream>
#include <stdexcept>

#include "../inc/core.hpp"
#include "../inc/utils.hpp"
#include "../inc/attacks/wordlist.hpp"

PassCracker::PassCracker(const std::string& password_file, const std::vector<size_t>& attack_ids){
    this->password_db = parse_shadow(password_file);
    // initialize each attack
    AttackType* new_attack;
    std::string candidate_path;
    size_t attack_count = attack_ids.size();
    for (int i = 0; i < attack_count; i++){
        // intialize the attack based on type
        switch (attack_ids[i])
        {
        case WORDLIST:
            std::cout << "Candidate file: ";
            std::getline(std::cin, candidate_path);
            new_attack = new WordlistCracker(candidate_path);
            break;
        default:
            throw std::runtime_error("unrecognized attack id. (If you're seeing this message, something has gone VERY wrong.)");
            break;
        }
        this->attacks.push_back(new_attack);
    }
}

PassCracker::~PassCracker(){
    size_t attack_count = this->attacks.size();
    for (int i = 0; i < attack_count; i++)
        delete this->attacks[i];
}

std::string PassCracker::crack_password(std::string target, bool multithread){
    // get the checksum
    if (!password_db.count(target))
        throw std::runtime_error("No user \"" + target + "\" found.");
    std::string checksum = password_db[target];
    // run the attack
    std::string result;
    size_t attack_count = attacks.size();
    for (size_t i = 0; i < attack_count; i++){
        result = attacks[i]->run_attack(checksum, multithread);
        if (result != "")
            return result;
    }
    return "";
}
