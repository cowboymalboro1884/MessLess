#include "encrypting.hpp"
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

[[nodiscard]] RSAKeys messless::Encrypting::create_keys() {
    CryptoPP::AutoSeededRandomPool rng;
    CryptoPP::InvertibleRSAFunction params;
    params.GenerateRandomWithKeySize(rng, 3072);
    RSA::PrivateKey privateKey(params);
    // NOLINTNEXTLINE
    RSA::PublicKey publicKey(params);
    return {publicKey, privateKey};
}

[[maybe_unused]] [[nodiscard]] PrivateKeys
Encrypting::to_normal_view_private_keys(const RSA::PrivateKey &r) {
    std::stringstream ss;
    ss << r.GetModulus() << ' ' << r.GetPrime1() << ' ' << r.GetPrime2() << ' '
       << r.GetPrivateExponent() << ' ' << r.GetPublicExponent();
    PrivateKeys new_keys;
    ss >> new_keys.modulus >> new_keys.first_prime >> new_keys.second_prime >>
        new_keys.private_exponent >> new_keys.public_exponent;
    return new_keys;
}

[[nodiscard]] PublicKeys Encrypting::to_normal_view_public_keys(
    const RSA::PublicKey &r
) {
    std::stringstream ss;
    ss << r.GetModulus() << r.GetPublicExponent();
    PublicKeys new_keys;
    ss >> new_keys.modulus >> new_keys.public_exponent;
    return new_keys;
}

[[nodiscard]] std::string
Encrypting::encrypt(const std::string &message, RSA::PublicKey &publicKey) {
    CryptoPP::AutoSeededRandomPool rng;
    CryptoPP::RSAES_OAEP_SHA_Encryptor e(publicKey);
    std::string cipher;
    CryptoPP::StringSource ss1(
        message, true,
        new CryptoPP::PK_EncryptorFilter(
            rng, e, new CryptoPP::StringSink(cipher)
        )
    );
    return cipher;
}

[[nodiscard]] std::string
Encrypting::decrypt(const std::string &message, RSA::PrivateKey &privateKey) {
    CryptoPP::RSAES_OAEP_SHA_Decryptor d(privateKey);
    CryptoPP::AutoSeededRandomPool rng;
    std::string recovered;
    CryptoPP::StringSource ss2(
        message, true,
        new CryptoPP::PK_DecryptorFilter(
            rng, d, new CryptoPP::StringSink(recovered)
        )
    );
    return recovered;
}

[[nodiscard]] RSA::PublicKey Encrypting::to_cryptopp_public_key(
    const PublicKeys &r
) {
    RSA::PublicKey x;
    std::stringstream ss;
    ss << r.modulus << ' ' << r.public_exponent;
    CryptoPP::Integer n, e;
    ss >> n >> e;
    x.Initialize(n, e);
    return x;
}

[[maybe_unused]] [[nodiscard]] RSA::PrivateKey
Encrypting::to_cryptopp_private_key(const PrivateKeys &r) {
    RSA::PrivateKey x;
    std::stringstream ss;
    ss << r.modulus << ' ' << r.first_prime << ' ' << r.second_prime << ' '
       << r.private_exponent << ' ' << r.public_exponent;
    CryptoPP::Integer n, p, q, d, e;
    ss >> n >> p >> q >> d >> e;
    x.Initialize(n, e, d);  // TODO maybe isn't correct
    return x;
}

}  // namespace messless
