#pragma once
#include "math/polynomial.h"

struct SecretKey {
    Polynomial s;
};

struct PublicKey {
    Polynomial p0;
    Polynomial p1;
};