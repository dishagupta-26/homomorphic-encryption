#pragma once
#include "scheme/params.h"
#include "scheme/keys.h"
#include "scheme/ciphertext.h"
#include "math/polynomial.h"

class Decryptor {
public:
    // The constructor takes the parameters and the SECRET key to decrypt with.
    Decryptor(const Parameters& params, const SecretKey& secret_key);

    // This function decrypts a ciphertext back into a plaintext polynomial.
    void decrypt(const Ciphertext& ciphertext, Polynomial& plain_poly);

private:
    const Parameters& params;
    const SecretKey& secret_key;
};