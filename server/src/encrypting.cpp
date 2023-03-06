#include "../include/encrypting.hpp"

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
    const std::string &first_salt,
    const std::string &second_salt
) {
    std::string result = password + second_salt + first_salt;
    for (int i = 0; i < 1024; ++i) {
        result = get_hash(result);
    }
    return result;
}

messless::Encrypting::Encrypting(const std::string &config_file) {
    std::ifstream input(config_file);
    std::getline(input, private_salt);
}
