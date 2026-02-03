#ifndef RLWE_KEYGEN_H
#define RLWE_KEYGEN_H

#include "math/poly.h"
#include "lattice/rlwe_params.h"

namespace fhe {

struct SecretKey {
    Polynomial s;
};

struct PublicKey {
    Polynomial a;
    Polynomial b;
};

class RLWEKeyGen {
public:
    static SecretKey generate_secret(const RLWEParams& params);
    static PublicKey generate_public(const RLWEParams& params,
                                     const SecretKey& sk);
};

} // namespace fhe

#endif
