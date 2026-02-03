#include "scheme/evaluator.h"
#include <vector>

Evaluator::Evaluator(const Parameters& params) : params(params) {}

void Evaluator::add(const Ciphertext& ct1, const Ciphertext& ct2, Ciphertext& result_ct) {
    // Homomorphic addition is simply component-wise polynomial addition.
    // result_ct.c0 = ct1.c0 + ct2.c0
    // result_ct.c1 = ct1.c1 + ct2.c1
    result_ct.c0 = ct1.c0.add(ct2.c0);
    result_ct.c1 = ct1.c1.add(ct2.c1);

    // Ensure the results remain within the modulus q
    for (size_t i = 0; i < params.poly_modulus_degree; ++i) {
        result_ct.c0.coefficients[i] %= params.ciphertext_modulus;
        result_ct.c1.coefficients[i] %= params.ciphertext_modulus;
    }
} 

void Evaluator::multiply(const Ciphertext& ct1, const Ciphertext& ct2, std::vector<Polynomial>& result_ct) {
    // Homomorphic multiplication involves several polynomial multiplications.
    Polynomial c0_prime = ct1.c0.multiply(ct2.c0, params);

    Polynomial p1 = ct1.c0.multiply(ct2.c1, params);
    Polynomial p2 = ct1.c1.multiply(ct2.c0, params);
    Polynomial c1_prime = p1.add(p2);

    Polynomial c2_prime = ct1.c1.multiply(ct2.c1, params);

    // Modulo the coefficients of the middle term
    for (size_t i = 0; i < params.poly_modulus_degree; ++i) {
        c1_prime.coefficients[i] %= params.ciphertext_modulus;
    }

    result_ct.clear();
    result_ct.push_back(c0_prime);
    result_ct.push_back(c1_prime);
    result_ct.push_back(c2_prime);
}