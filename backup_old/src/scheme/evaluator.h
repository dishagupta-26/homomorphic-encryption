#pragma once
#include "scheme/params.h"
#include "scheme/ciphertext.h"

class Evaluator {
public:
    Evaluator(const Parameters& params);

    // Homomorphically adds two ciphertexts.
    void add(const Ciphertext& ct1, const Ciphertext& ct2, Ciphertext& result_ct);
    // Homomorphically multiplies two ciphertexts.
    void multiply(const Ciphertext& ct1, const Ciphertext& ct2, std::vector<Polynomial>& result_ct);


private:
    const Parameters& params;
};