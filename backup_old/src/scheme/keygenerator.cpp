#include "scheme/keygenerator.h"
#include "math/polynomial.h"
#include "math/ntt.h"       // We need NTT for the fast multiplication
#include <random>           // For C++'s modern random number generation

// A helper function to generate a polynomial with small coefficients {-1, 0, 1}
static Polynomial generate_small_polynomial(size_t n, uint64_t modulus) {
    // Use C++'s <random> library for high-quality random numbers
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(-1, 1);

    Polynomial p(n - 1);
    for (size_t i = 0; i < n; ++i) {
        int64_t val = distrib(gen);
        // We handle negative numbers by adding the modulus. e.g., -1 becomes q-1.
        p.coefficients[i] = (val < 0) ? (modulus + val) : val;
    }
    return p;
}

// A helper function to generate a polynomial with large, uniform random coefficients
static Polynomial generate_uniform_polynomial(size_t n, uint64_t modulus) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<uint64_t> distrib(0, modulus - 1);

    Polynomial p(n - 1);
    for (size_t i = 0; i < n; ++i) {
        p.coefficients[i] = distrib(gen);
    }
    return p;
}


KeyGenerator::KeyGenerator(const Parameters& params) : params(params) {}

void KeyGenerator::generate(SecretKey& secret_key, PublicKey& public_key) {
    // 1. Generate the secret key 's', which is a small polynomial.
    secret_key.s = generate_small_polynomial(params.poly_modulus_degree, params.ciphertext_modulus);

    // 2. Generate the public key's uniformly random polynomial 'a'. This will be p₁.
    public_key.p1 = generate_uniform_polynomial(params.poly_modulus_degree, params.ciphertext_modulus);

    // 3. Generate the small error polynomial 'e'.
    Polynomial e = generate_small_polynomial(params.poly_modulus_degree, params.ciphertext_modulus);

    // 4. Calculate p₀ = -(a * s) + e
    
    // First, find the product a*s using our fast NTT-based multiplication
    Polynomial a_times_s = public_key.p1.multiply(secret_key.s, params);

    // Now, calculate p₀. We do all calculations modulo q.
    public_key.p0.coefficients.resize(params.poly_modulus_degree);
    for (size_t i = 0; i < params.poly_modulus_degree; ++i) {
        // -(a*s) is calculated as (q - (a*s))
        uint64_t neg_a_s = params.ciphertext_modulus - a_times_s.coefficients[i];
        
        // Add the error polynomial 'e'
        public_key.p0.coefficients[i] = (neg_a_s + e.coefficients[i]) % params.ciphertext_modulus;
    }
}