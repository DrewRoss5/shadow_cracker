#include <string>
#include <vector>
#include <functional>
#include <unordered_map>
#include "attacks/attack.hpp"


enum attacks{
    WORDLIST
};

class PassCracker{
    public:
        PassCracker() {};
        PassCracker(const std::string& password_file, const std::vector<size_t>& attack_ids);
        ~PassCracker();
        std::string crack_password(std::string target);
    private:
        std::unordered_map<std::string, std::string> password_db;
        std::vector<AttackType*> attacks;

};