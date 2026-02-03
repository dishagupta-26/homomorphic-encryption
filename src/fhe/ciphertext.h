#ifndef CIPHERTEXT_H
#define CIPHERTEXT_H

#include "math/poly.h"

namespace fhe {

struct Ciphertext {
    Polynomial c0;
    Polynomial c1;
};

} // namespace fhe

#endif
