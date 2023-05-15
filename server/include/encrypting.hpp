#ifndef ENCRYPTING_HPP
#define ENCRYPTING_HPP

#include <fstream>
#include<sstream>
#include "cryptopp/base64.h"
#include "cryptopp/config_int.h"
#include "cryptopp/filters.h"
#include "cryptopp/integer.h"
#include "cryptopp/randpool.h"
#include "cryptopp/sha.h"
#include "cryptopp/rsa.h"
#include "cryptopp/osrng.h"

namespace messless {
class RSA
{
public:
    typedef CryptoPP::RSAFunction PublicKey;
    typedef CryptoPP::InvertibleRSAFunction PrivateKey;
};

class RSAKeys
{
public:
     RSA::PublicKey PublicKey;
     RSA::PrivateKey PrivateKey;
};
class PrivateKeys{
public:
    std::string modulus;
    std::string first_prime;
    std::string second_prime;
    std::string public_exponent;
    std::string private_exponent;
};
class PublicKeys{
public:
    std::string modulus;
    std::string public_exponent;
};
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
    [[nodiscard]] static RSAKeys create_keys();
    [[maybe_unused]] [[nodiscard]] static PrivateKeys to_normal_view_private_keys(const RSA::PrivateKey& r);
    [[nodiscard]] static PublicKeys to_normal_view_public_keys(const RSA::PublicKey & r);
    [[nodiscard]] static RSA::PublicKey to_cryptopp_public_key(const PublicKeys& r);
    [[maybe_unused]][[nodiscard]] static RSA::PrivateKey to_cryptopp_private_key(const PrivateKeys& r);
    [[nodiscard]] static std::string encrypt(const std::string &message,RSA::PublicKey &publicKey);
    [[nodiscard]] static std::string decrypt(const std::string &message,RSA::PrivateKey  &privateKey);
};
}  // namespace messless
#endif
