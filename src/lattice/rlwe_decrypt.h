#ifndef RLWE_DECRYPT_H
#define RLWE_DECRYPT_H

#include "lattice/rlwe_keygen.h"
#include "lattice/rlwe_params.h"
#include "fhe/ciphertext.h"

namespace fhe {

class RLWEDecrypt {
public:
    static Polynomial decrypt(const SecretKey& sk,
                              const Ciphertext& ct,
                              const RLWEParams& params);
};

} // namespace fhe

#endif
