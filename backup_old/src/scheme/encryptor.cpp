#include "scheme/encryptor.h"
#include <random> // For generating the new random polynomials

// Helper function to generate a polynomial with small coefficients {-1, 0, 1}
static Polynomial generate_small_polynomial(size_t n, uint64_t modulus) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(-1, 1);
    Polynomial p(n - 1);
    for (size_t i = 0; i < n; ++i) {
        int64_t val = distrib(gen);
        p.coefficients[i] = (val < 0) ? (modulus + val) : val;
    }
    return p;
}

Encryptor::Encryptor(const Parameters& params, const PublicKey& public_key)
    : params(params), public_key(public_key) {}

void Encryptor::encrypt(const Polynomial& plain_poly, Ciphertext& ciphertext) {
    // 1. Generate new small random polynomials u, e₁, e₂ needed for encryption
    Polynomial u = generate_small_polynomial(params.poly_modulus_degree, params.ciphertext_modulus);
    Polynomial e1 = generate_small_polynomial(params.poly_modulus_degree, params.ciphertext_modulus);
    Polynomial e2 = generate_small_polynomial(params.poly_modulus_degree, params.ciphertext_modulus);

    // 2. Calculate c₀ = p₀*u + e₁ + m
    Polynomial temp1 = public_key.p0.multiply(u, params);
    Polynomial temp2 = temp1.add(e1);
    ciphertext.c0 = temp2.add(plain_poly);
    
    for (size_t i = 0; i < params.poly_modulus_degree; ++i) {
        ciphertext.c0.coefficients[i] %= params.ciphertext_modulus;
    }

    // 3. Calculate c₁ = p₁*u + e₂
    Polynomial temp3 = public_key.p1.multiply(u, params);
    ciphertext.c1 = temp3.add(e2);

    for (size_t i = 0; i < params.poly_modulus_degree; ++i) {
        ciphertext.c1.coefficients[i] %= params.ciphertext_modulus;
    }
}