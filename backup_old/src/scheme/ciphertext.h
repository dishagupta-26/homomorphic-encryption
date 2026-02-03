#pragma once
#include "math/polynomial.h"

// A Ciphertext in our scheme consists of a pair of polynomials, (c₀, c₁).
struct Ciphertext {
    Polynomial c0;
    Polynomial c1;
};