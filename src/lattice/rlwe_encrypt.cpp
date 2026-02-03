#include "lattice/rlwe_encrypt.h"
#include "utils/random.h"
#include "math/mod_arith.h"

namespace fhe {

Ciphertext RLWEEncrypt::encrypt(const RLWEParams& params,
                                const PublicKey& pk,
                                const Polynomial& message) {

    Polynomial u(params.n, params.q);
    Polynomial e1(params.n, params.q);
    Polynomial e2(params.n, params.q);

    for (size_t i = 0; i < params.n; i++) {
        u.coeffs[i]  = small_noise(1);
        e1.coeffs[i] = small_noise(params.noise);
        e2.coeffs[i] = small_noise(params.noise);
    }

    Polynomial bu = pk.b.mul_naive(u);
    Polynomial au = pk.a.mul_naive(u);

    Polynomial scaled_m = message;
    int64_t Delta = params.q / params.t;

    for (auto& c : scaled_m.coeffs)
        c = fhe::mod(c * Delta, params.q);

    Polynomial c0 = bu.add(e1).add(scaled_m);

    Polynomial c1 = au.add(e2);

    c0.reduce();
    c1.reduce();

    return {c0, c1};
}

} // namespace fhe
