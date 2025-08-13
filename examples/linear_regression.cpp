#include <iostream>
#include <vector>
#include "scheme/params.h"
#include "math/polynomial.h"
#include "math/ntt.h"

// Helper function to print a vector of coefficients
void print_poly(const std::string& label, const std::vector<uint64_t>& poly_coeffs) {
    std::cout << label;
    for(uint64_t coeff : poly_coeffs) { std::cout << coeff << " "; }
    std::cout << std::endl;
}

int main() {
    std::cout << "--- FHE Framework: NTT Round-Trip Test ---" << std::endl;

    Parameters params;
    params.poly_modulus_degree = 8;  // N
    params.ciphertext_modulus = 17; // q

    // Create a sample polynomial
    Polynomial p(params.poly_modulus_degree - 1);
    p.coefficients = {1, 2, 3, 4, 5, 0, 0, 0};
    
    // Save a copy of the original coefficients to compare against later
    std::vector<uint64_t> original_coeffs = p.coefficients;
    print_poly("Original poly:      ", original_coeffs);

    // 1. Apply the forward NTT
    NTT::forward(p, params);
    print_poly("After forward NTT:  ", p.coefficients);

    // 2. Apply the inverse NTT
    NTT::inverse(p, params);
    print_poly("After inverse NTT:  ", p.coefficients);

    // 3. Verify the result
    if (p.coefficients == original_coeffs) {
        std::cout << "\nSUCCESS: The INTT correctly recovered the original polynomial." << std::endl;
    } else {
        std::cout << "\nFAILURE: The INTT did not recover the original polynomial." << std::endl;
    }

    std::cout << "\n--- Test Complete ---" << std::endl;
    return 0;
}