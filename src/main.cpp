#include <iostream>
#include <unistd.h>
#include <unordered_map>

#include "../inc/core.hpp"
#include "../inc/utils.hpp"

int main(int argc, char** argv){
    // this is to associate each attack type with it's ID
    std::unordered_map<std::string, size_t> attack_type_dict = {
        {"wordlist", WORDLIST}
    };
    // get the password file path
    std::string password_file, attack_type_str;
    std::cout << "Password file: ";
    std::getline(std::cin, password_file);
    // get each attack type
    std::getline(std::cin, attack_type_str);
    std::vector<std::string> attack_types = split_str(attack_type_str, ' ');
    std::vector<size_t> attack_ids;
    for (size_t i = 0; i < attack_types.size(); i++){
        if (!attack_type_dict.count(attack_types[i])){
            print_err("Invalid attack type: " + attack_types[i]);
            return 1;
        }
        attack_ids.push_back(attack_type_dict[attack_types[i]]);
    }
    // initialize the attack engine
    std::cout << "Initializing attack engine..." << std::endl;
    PassCracker cracker;
    try{
        cracker = PassCracker(password_file, attack_ids);
    }
    catch (std::runtime_error e){
        print_err(e.what());
        return 1;
    }
    // run the attack
    std::string target, result;
    std::cout << "Target: ";
    std::getline(std::cin, target);
    std::cout << "Finding password..." << std::endl;
    try{
        result = cracker.crack_password(target, false);
    }
    catch (std::runtime_error e){
        print_err(e.what());
        return 1;
    }
    if (result == "")
        std::cout << "NO MATCH FOUND" << std::endl;
    else 
        std::cout << "MATCH FOUND: " << result << std::endl;
    return 0;
}