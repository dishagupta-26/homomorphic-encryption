#ifndef RLWE_PARAMS_H
#define RLWE_PARAMS_H

#include <cstddef>
#include <cstdint>

namespace fhe {

struct RLWEParams {
    size_t n;        // ring dimension
    int64_t q;       // ciphertext modulus
    int64_t t;       // plaintext modulus
    int64_t noise;   // noise bound

    RLWEParams(size_t degree,
               int64_t modulus,
               int64_t plaintext_modulus,
               int64_t noise_bound)
        : n(degree),
          q(modulus),
          t(plaintext_modulus),
          noise(noise_bound) {}
};

} // namespace fhe

#endif // RLWE_PARAMS_H
