#ifndef MOD_ARITH_H
#define MOD_ARITH_H

#include <cstdint>

namespace fhe {

// Correct modulo (always non-negative)
inline int64_t mod(int64_t a, int64_t q) {
    int64_t r = a % q;
    return (r < 0) ? r + q : r;
}

// Modular addition
inline int64_t mod_add(int64_t a, int64_t b, int64_t q) {
    return mod(a + b, q);
}

// Modular subtraction
inline int64_t mod_sub(int64_t a, int64_t b, int64_t q) {
    return mod(a - b, q);
}

// Modular multiplication
inline int64_t mod_mul(int64_t a, int64_t b, int64_t q) {
    return mod(a * b, q);
}

// Modular exponentiation (a^e mod q)
inline int64_t mod_pow(int64_t base, int64_t exp, int64_t q) {
    int64_t result = 1;
    base = mod(base, q);

    while (exp > 0) {
        if (exp & 1)
            result = mod_mul(result, base, q);
        base = mod_mul(base, base, q);
        exp >>= 1;
    }
    return result;
}

} // namespace fhe

#endif
