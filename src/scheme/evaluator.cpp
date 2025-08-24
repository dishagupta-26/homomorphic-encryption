#include "scheme/evaluator.h"

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
