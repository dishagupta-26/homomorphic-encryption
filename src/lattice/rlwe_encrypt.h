#ifndef RLWE_ENCRYPT_H
#define RLWE_ENCRYPT_H

#include "lattice/rlwe_keygen.h"
#include "lattice/rlwe_params.h"
#include "fhe/ciphertext.h"

namespace fhe {

class RLWEEncrypt {
public:
    static Ciphertext encrypt(const RLWEParams& params,
                              const PublicKey& pk,
                              const Polynomial& message);
};

} // namespace fhe

#endif
