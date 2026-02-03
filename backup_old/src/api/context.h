#pragma once
#include "scheme/params.h"
#include "scheme/ciphertext.h"
#include <cstdint>

class KeyGenerator;
class Encryptor;
class Decryptor;
class Evaluator;
struct SecretKey;
struct PublicKey;

class FHE {
public:
    FHE(const Parameters& params);
    ~FHE();

    void generate_keys();
    Ciphertext encrypt(int64_t message);
    int64_t decrypt(const Ciphertext& ciphertext);
    Ciphertext add(const Ciphertext& ct1, const Ciphertext& ct2);

private:
    Parameters params;
    // Using pointers to hide the full struct definitions from the user
    SecretKey* secret_key;
    PublicKey* public_key;
    KeyGenerator* keygen;
    Encryptor* encryptor;
    Decryptor* decryptor;
    Evaluator* evaluator;
};