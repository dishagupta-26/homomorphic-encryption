#include "scheme/decryptor.h"
#include <vector>

Decryptor::Decryptor(const Parameters& params, const SecretKey& secret_key)
    : params(params), secret_key(secret_key) {}

void Decryptor::decrypt(const Ciphertext& ciphertext, Polynomial& plain_poly) {
    // To decrypt, we compute the message m' = c₀ + c₁ * s

    // 1. Calculate the product c₁ * s using our fast NTT multiplication.
    Polynomial c1_times_s = ciphertext.c1.multiply(secret_key.s, params);

    // 2. Add c₀ to the result from the previous step.
    plain_poly = ciphertext.c0.add(c1_times_s);

    // 3. Ensure all coefficients are brought back into the modulus q.
    for (size_t i = 0; i < params.poly_modulus_degree; ++i) {
        plain_poly.coefficients[i] %= params.ciphertext_modulus;
    }

    // At this point, plain_poly.coefficients[0] should be our original message
    // plus a small amount of noise. For our simple parameters, the noise will
    // be small enough that the result is still correct.
    // A real FHE library would have a more complex decoding step here.
}

void Decryptor::decrypt_multiplied(const std::vector<Polynomial>& ciphertext, Polynomial& plain_poly) {
    // Decrypts a 3-part ciphertext from multiplication: m' = c'₀ + c'₁*s + c'₂*s²

    // 1. Calculate s²
    Polynomial s_squared = secret_key.s.multiply(secret_key.s, params);

    // 2. Calculate c'₁*s
    Polynomial c1_s = ciphertext[1].multiply(secret_key.s, params);

    // 3. Calculate c'₂*s²
    Polynomial c2_s_sq = ciphertext[2].multiply(s_squared, params);

    // 4. Sum everything: c'₀ + c'₁*s + c'₂*s²
    Polynomial temp = ciphertext[0].add(c1_s);
    plain_poly = temp.add(c2_s_sq);

    // 5. Final modulo
    for (size_t i = 0; i < params.poly_modulus_degree; ++i) {
        plain_poly.coefficients[i] %= params.ciphertext_modulus;
    }
}
