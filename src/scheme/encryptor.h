#pragma once
#include "scheme/params.h"
#include "scheme/keys.h"
#include "scheme/ciphertext.h"
#include "math/polynomial.h"

class Encryptor {
public:
    // The constructor takes the parameters and the public key to encrypt with.
    Encryptor(const Parameters& params, const PublicKey& public_key);

    // This function encrypts a plaintext polynomial into a ciphertext.
    void encrypt(const Polynomial& plain_poly, Ciphertext& ciphertext);

private:
    const Parameters& params;
    const PublicKey& public_key;
};