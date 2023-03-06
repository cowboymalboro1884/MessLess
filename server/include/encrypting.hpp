#ifndef ENCRYPTING_HPP
#define ENCRYPTING_HPP

#include <fstream>
#include "cryptopp/base64.h"
#include "cryptopp/filters.h"
#include "cryptopp/integer.h"
#include "cryptopp/sha.h"

namespace messless {

class Encrypting {
    std::string private_salt;
    static std::string get_hash(std::string &str);

public:
    explicit Encrypting(const std::string &config_file);
    std::string get_password_hash(
        const std::string &password,
        const std::string &first_salt,
        const std::string &second_salt
    );
};
}  // namespace messless
#endif
