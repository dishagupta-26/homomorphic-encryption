#include "lattice/rlwe_keygen.h"
#include "utils/random.h"
#include "math/mod_arith.h"

namespace fhe {

SecretKey RLWEKeyGen::generate_secret(const RLWEParams& params) {
    Polynomial s(params.n, params.q);

    for (size_t i = 0; i < params.n; i++)
        s.coeffs[i] = small_noise(1); // {-1, 0, 1}

    s.reduce();
    return {s};
}

PublicKey RLWEKeyGen::generate_public(const RLWEParams& params,
                                      const SecretKey& sk) {
    Polynomial a(params.n, params.q);
    Polynomial e(params.n, params.q);

    for (size_t i = 0; i < params.n; i++) {
        a.coeffs[i] = uniform_int(0, params.q - 1);
        e.coeffs[i] = small_noise(params.noise);
    }

    Polynomial as = a.mul_naive(sk.s);
    Polynomial neg_as(params.n, params.q);

    for (size_t i = 0; i < params.n; i++)
        neg_as.coeffs[i] = mod(-as.coeffs[i], params.q);

    Polynomial b = neg_as.add(e);
    b.reduce();

    return {a, b};
}

} // namespace fhe
