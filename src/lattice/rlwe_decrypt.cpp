#include "lattice/rlwe_decrypt.h"

namespace fhe {

Polynomial RLWEDecrypt::decrypt(const SecretKey& sk,
                                const Ciphertext& ct,
                                const RLWEParams& params) {

    Polynomial c1s = ct.c1.mul_naive(sk.s);
    Polynomial m_scaled = ct.c0.add(c1s);
    m_scaled.reduce();

    int64_t Delta = params.q / params.t;

    Polynomial m(params.n, params.q);
    for (size_t i = 0; i < params.n; i++) {
        // nearest integer decoding
        m.coeffs[i] = (m_scaled.coeffs[i] + Delta/2) / Delta;
        m.coeffs[i] %= params.t;
    }
    return m;
}


} // namespace fhe
