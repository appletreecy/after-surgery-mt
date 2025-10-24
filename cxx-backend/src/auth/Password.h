// Password.h
#pragma once
#include <string>
namespace pw {
    std::string hash(const std::string &plain);      // argon2id
    bool verify(const std::string &plain, const std::string &encoded);
}
