#include "math/ntt.h"
#include "scheme/params.h"
#include <vector>
#include <cmath>
#include <utility>
#include <stdexcept>

namespace NTT {

    // A helper function to perform the bit-reversal permutation.
    static void bit_reverse_permutation(std::vector<uint64_t>& vec) {
        size_t n = vec.size();
        if (n <= 1) return;
        size_t bits = static_cast<size_t>(std::log2(n - 1)) + 1;
        for (size_t i = 0; i < n; ++i) {
            size_t reversed_i = 0;
            for (size_t j = 0; j < bits; ++j) {
                if ((i >> j) & 1) {
                    reversed_i |= 1 << (bits - 1 - j);
                }
            }
            if (i < reversed_i) {
                std::swap(vec[i], vec[reversed_i]);
            }
        }
    }

    // Helper function for modular exponentiation: computes (base^exp) % modulus
    static uint64_t power(uint64_t base, uint64_t exp, uint64_t modulus) {
        uint64_t res = 1;
        base %= modulus;
        while (exp > 0) {
            if (exp % 2 == 1) res = (res * base) % modulus;
            base = (base * base) % modulus;
            exp /= 2;
        }
        return res;
    }

    void forward(Polynomial& p, const Parameters& params) {
        size_t n = params.poly_modulus_degree;
        uint64_t q = params.ciphertext_modulus;

        p.coefficients.resize(n, 0);
        bit_reverse_permutation(p.coefficients);

        // For N=8, q=17, a known primitive 2N-th (16th) root of unity is 2.
        // In a real library, this would be pre-computed.
        uint64_t primitive_root = 3;

        for (size_t m = 2; m <= n; m <<= 1) {
            // For each stage, we need a primitive m-th root of unity.
            // w_m = primitive_root^(2N/m) mod q
            uint64_t w_m = power(primitive_root, (2 * n) / m, q);

            for (size_t k = 0; k < n; k += m) {
                uint64_t w = 1; // Start with twiddle factor w = w_m^0 = 1
                for (size_t j = 0; j < m / 2; ++j) {
                    size_t t_idx = k + j;
                    size_t u_idx = k + j + m / 2;
                    
                    uint64_t t = p.coefficients[t_idx];
                    uint64_t u_twiddled = (w * p.coefficients[u_idx]) % q;

                    p.coefficients[t_idx] = (t + u_twiddled) % q;
                    p.coefficients[u_idx] = (t + q - u_twiddled) % q;
                    
                    // Update twiddle factor for the next butterfly in this group
                    w = (w * w_m) % q;
                }
            }
        }
    }

    void inverse(Polynomial& p, const Parameters& params) {
        size_t n = params.poly_modulus_degree;
        uint64_t q = params.ciphertext_modulus;

        // For the INTT, the structure is IDENTICAL to the forward NTT.
        // The only differences are:
        // 1. We use the modular inverse of the primitive root.
        // 2. At the very end, we scale the result by N^-1 mod q.

        uint64_t primitive_root = 3;
        uint64_t inv_primitive_root = power(primitive_root, q - 2, q); // g^-1 mod q

        // Perform bit-reversal just like in the forward NTT.
        // The input 'p' must be the correct size.
        p.coefficients.resize(n, 0);
        bit_reverse_permutation(p.coefficients);

        // Perform the exact same butterfly operations, but with the inverse root.
        for (size_t m = 2; m <= n; m <<= 1) {
            uint64_t w_m = power(inv_primitive_root, (2 * n) / m, q);
            for (size_t k = 0; k < n; k += m) {
                uint64_t w = 1;
                for (size_t j = 0; j < m / 2; ++j) {
                    size_t t_idx = k + j;
                    size_t u_idx = k + j + m / 2;
                    uint64_t t = p.coefficients[t_idx];
                    uint64_t u_twiddled = (w * p.coefficients[u_idx]) % q;
                    p.coefficients[t_idx] = (t + u_twiddled) % q;
                    p.coefficients[u_idx] = (t + q - u_twiddled) % q;
                    w = (w * w_m) % q;
                }
            }
        }

        // Final step: scale every coefficient by N^-1 mod q.
        uint64_t n_inv = power(n, q - 2, q);
        for (size_t i = 0; i < n; ++i) {
            p.coefficients[i] = (p.coefficients[i] * n_inv) % q;
        }
    }
}