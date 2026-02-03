#pragma once
#include <cstdint>

class Parameters {
public:
    // --- Polynomial Parameters ---
    // The degree of the polynomial ring. For the NTT we will implement,
    // this MUST be a power of 2.
    size_t poly_modulus_degree; // N

    // --- Ciphertext Modulus ---
    // A special prime number 'q' that will be the modulus for our calculations.
    // For NTT to work, 'q' must be a prime such that q = 1 (mod 2N).
    uint64_t ciphertext_modulus; // q
};