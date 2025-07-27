#include <iostream>
#include <unistd.h>
#include <unordered_map>
#include <boost/program_options.hpp>

#include "../inc/core.hpp"
#include "../inc/utils.hpp"

namespace po = boost::program_options;

int main(int argc, char** argv){
    // parse command line options
    po::options_description description("ShadowCracker version 0.1.0\nProgram Options");
    description.add_options()
        ("help", "display this menu")
        ("input-file",   po::value<std::string>()->default_value(""),         "Specify the shadow file to find a password for")
        ("target-user",  po::value<std::string>()->default_value(""),         "Specify the user whose password you'd like to find")
        ("attack-type", po::value<std::string>()->default_value("wordlist"), "Specify the attack type to be run. At the moment, this only supports wordlist attacks.")
        ("thread-count", po::value<size_t>()->default_value(1),                  "Specify the number of threads the attack should use (default = 1)")
    ;
    po::variables_map var_map;
    po::store(po::parse_command_line(argc, argv, description), var_map);
    po::notify(var_map);   
    // determine if the user wants to view the help menu
    if (var_map.count("help")){
        std::cout << description << std::endl;
        return 0;
    }
    // this is to associate each attack type with it's ID
    std::unordered_map<std::string, size_t> attack_type_dict = {
        {"wordlist", WORDLIST}
    };
    // ensure the required arguments are provided
    for (const std::string& param : {"input-file", "target-user"}){
        if (!var_map.count(param)){
            print_err(param + " is required.");
            return 1;
        }
    }
    std::string input_file {var_map["input-file"].as<std::string>()}, target{var_map["target-user"].as<std::string>()};
    // convert the attack type to an ID
    std::string attack_type = var_map["attack-type"].as<std::string>();
    if (!attack_type_dict.count(attack_type)){
        print_err("unrecognized attack type: " + attack_type);
        return 1;
    }
    size_t attack_id = attack_type_dict[attack_type];
    // run the attack
    PassCracker cracker(input_file, {attack_id});
    std::string result;
    try{
        std::cout << "Finding password for " << target << "..." << std::endl;
        result = cracker.crack_password(target, var_map["thread-count"].as<size_t>());
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