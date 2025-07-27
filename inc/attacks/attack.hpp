#include <vector>
#include <string>

#ifndef ATTACK_TYPE_H
#define ATTACK_TYPE_H

class AttackType{
    public:
        virtual std::string run_attack(const std::string& checksum, size_t thread_count) = 0;
};

#endif