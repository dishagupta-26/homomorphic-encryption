#include <iostream>
#include <vector>
#include "scheme/params.h"
#include "math/polynomial.h"
#include "math/ntt.h"

int main() {
    std::cout << "--- FHE Framework: NTT Bit-Reversal Test ---" << std::endl;

    Parameters params;
    params.poly_modulus_degree = 8;  // N
    params.ciphertext_modulus = 17; // q

    // Create a sample polynomial with coefficients 0, 1, 2, ..., 7
    Polynomial p(params.poly_modulus_degree - 1);
    for (size_t i = 0; i < params.poly_modulus_degree; ++i) {
        p.coefficients[i] = i;
    }

    std::cout << "Original coefficients:     ";
    for(uint64_t coeff : p.coefficients) { std::cout << coeff << " "; }
    std::cout << std::endl;

    // Apply the forward NTT (which currently only does bit-reversal)
    NTT::forward(p, params);

    std::cout << "After bit-reversal:      ";
    for(uint64_t coeff : p.coefficients) { std::cout << coeff << " "; }
    std::cout << std::endl;
    
    std::cout << "Expected order for N=8:  0 4 2 6 1 5 3 7" << std::endl;

    std::cout << "\n--- Test Complete ---" << std::endl;
    return 0;
}