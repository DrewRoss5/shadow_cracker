#include <iostream>
#include <unistd.h>

#include "../inc/utils.hpp"

int main(int argc, char** argv){
    std::string hash = "$6$vyrh7VK047rfFPKb$GkHuG9MOcNNJIxXTacj5fEw0UR3UpE9rfOV//b1DbVdwp3k6ZIAi6S0p3.w0lMhVpbnPR8rKvGigKBVRFaO0y/";
    std::vector<std::string> passwords = {"Password123", "admin", "1234567890", "WrongAgain", "wonderland"};
    std::cout << "Finding password for Alice..." << std::endl;
    for (const std::string& candidate : passwords){
        std::cout << candidate << "....";
        if (check_pass(candidate, hash))
            std::cout << "MATCH FOUND" << std::endl;
        else
            std::cout << "NO MATCH" << std::endl;
    }
    return 0;
}