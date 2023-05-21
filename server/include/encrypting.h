#ifndef ENCRYPTING_HPP
#define ENCRYPTING_HPP

#include <fstream>
#include "cryptopp/base64.h"
#include "cryptopp/config_int.h"
#include "cryptopp/filters.h"
#include "cryptopp/integer.h"
#include "cryptopp/randpool.h"
#include "cryptopp/sha.h"

namespace messless {

class Encrypting {
    std::string private_salt;
    static std::string get_hash(std::string &str);

public:
    static std::string get_random_string();
    Encrypting();
    explicit Encrypting(std::string salt);
    std::string get_password_hash(
        const std::string &password,
        const std::string &personal_salt
    );
};
}  // namespace messless
#endif
