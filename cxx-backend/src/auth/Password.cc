// Password.cc
#include "Password.h"
#include <argon2.h>
#include <vector>
#include <random>
#include <sstream>
#include <iomanip>

static std::string b64(const std::string &in) { // minimal; or use a lib
    static const char* tbl="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    std::string out; int val=0,valb=-6;
    for (uint8_t c: in){ val=(val<<8)+c; valb+=8;
        while(valb>=0){ out.push_back(tbl[(val>>valb)&0x3F]); valb-=6; } }
    while(valb>-6){ out.push_back(tbl[((val<<8)>>(valb+8))&0x3F]); valb-=6; }
    while(out.size()%4) out.push_back('=');
    return out;
}

namespace pw {
    std::string hash(const std::string &plain){
        // random salt
        std::random_device rd; std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dist(0,255);
        std::string salt(16,'\0');
        for(auto &c: salt) c = static_cast<char>(dist(gen));

        std::vector<uint8_t> out(32);
        if (argon2id_hash_raw(3, 1<<16, 1, plain.data(), plain.size(),
             salt.data(), salt.size(), out.data(), out.size()) != ARGON2_OK) {
            throw std::runtime_error("argon2id failed");
             }
        std::ostringstream oss;
        oss<<"$argon2id$v=19$m=65536,t=3,p=1$"
           << b64(salt) << "$" << b64(std::string((char*)out.data(), out.size()));
        return oss.str();
    }

    bool verify(const std::string &plain, const std::string &encoded){
        // For brevity, use argon2_verify on encoded string (needs full parser).
        // In practice, use a small parser or bring a helper lib.
        return argon2id_verify(encoded.c_str(), plain.data(), plain.size())==ARGON2_OK;
    }
}
