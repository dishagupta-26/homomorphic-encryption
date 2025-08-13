#include "math/ntt.h"
#include "scheme/params.h"
#include <vector>
#include <stdexcept> // For std::runtime_error
#include <cmath>    // For std::log2
#include <utility>  // For std::swap

namespace NTT {

    // A helper function to perform the bit-reversal permutation.
    // This is a "static" function, meaning it's only visible inside this .cpp file.
    static void bit_reverse_permutation(std::vector<uint64_t>& vec) {
        size_t n = vec.size();
        if (n <= 1) return;

        // The number of bits needed to represent indices up to n-1
        size_t bits = static_cast<size_t>(std::log2(n - 1)) + 1;

        for (size_t i = 0; i < n; ++i) {
            size_t reversed_i = 0;
            for (size_t j = 0; j < bits; ++j) {
                if ((i >> j) & 1) { // If the j-th bit of i is 1...
                    // ...set the corresponding bit in the reversed index.
                    reversed_i |= 1 << (bits - 1 - j);
                }
            }

            // Swap the elements only if the original index is less than the reversed one.
            // This clever trick ensures we don't swap the same pair of elements twice.
            if (i < reversed_i) {
                std::swap(vec[i], vec[reversed_i]);
            }
        }
    }

    void forward(Polynomial& p, const Parameters& params) {
        // Step 1: Make sure the polynomial's coefficient vector has the correct size (N).
        // If it's smaller, pad it with zeros. This is important.
        p.coefficients.resize(params.poly_modulus_degree, 0);

        // Step 2: Perform the bit-reversal permutation on the coefficients.
        bit_reverse_permutation(p.coefficients);
        
        // We will stop here for this step. The next parts of the NTT will go here.
        // We can now remove the "not implemented" error.
    }

    void inverse(Polynomial& p, const Parameters& params) {
        // We will implement this later.
        throw std::runtime_error("Inverse NTT is not yet implemented.");
    }
}