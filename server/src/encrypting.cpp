#include "../include/encrypting.hpp"
#include <iostream>

namespace messless {
std::string messless::Encrypting::get_hash(std::string &str) {
    std::string new_string;
    CryptoPP::SHA256 hash;

    CryptoPP::StringSource foo(
        str, true,
        new CryptoPP::HashFilter(
            hash,
            new CryptoPP::Base64Encoder(new CryptoPP::StringSink(new_string))
        )
    );

    return new_string;
}

std::string messless::Encrypting::get_password_hash(
    const std::string &password,
    const std::string &personal_salt
) {
    std::string result = password + personal_salt + private_salt;
    for (int i = 0; i < 1024; ++i) {
        result = get_hash(result);
    }
    return result;
}

messless::Encrypting::Encrypting(std::string salt)
    : private_salt(std::move(salt)) {
}

messless::Encrypting::Encrypting() : private_salt() {
}

std::string messless::Encrypting::get_random_string() {
    static CryptoPP::RandomPool current;
    static std::string str;
    str = CryptoPP::WordToString(current.GenerateWord32()) +
          CryptoPP::WordToString(current.GenerateWord32()) +
          CryptoPP::WordToString(current.GenerateWord32()) +
          CryptoPP::WordToString(current.GenerateWord32());
    return get_hash(str);
}
}  // namespace messless