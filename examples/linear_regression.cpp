#include <iostream>
#include <vector>
#include "scheme/params.h"
#include "math/polynomial.h"

int main() {
    std::cout << "--- FHE Framework: NTT-based Multiplication Test ---" << std::endl;

    Parameters params;
    params.poly_modulus_degree = 8;
    params.ciphertext_modulus = 17;

    // p1 = 2x + 3
    Polynomial p1(1);
    p1.coefficients = {3, 2};
    std::cout << "p1 = " << p1.to_string() << std::endl;

    // p2 = 4x + 5
    Polynomial p2(1);
    p2.coefficients = {5, 4};
    std::cout << "p2 = " << p2.to_string() << std::endl;
    std::cout << "--------------------------------" << std::endl;

    // Multiply p1 and p2 using our new NTT-based method
    Polynomial product = p1.multiply(p2, params);

    // Schoolbook result: (2x+3)*(4x+5) = 8x^2 + 10x + 12x + 15 = 8x^2 + 22x + 15
    // Modulo 17, this becomes: 8x^2 + 5x + 15
    std::cout << "NTT-based product: " << product.to_string() << std::endl;
    std::cout << "Expected result:   8x^2 + 5x^1 + 15x^0" << std::endl;
    
    std::cout << "\n--- Test Complete ---" << std::endl;
    return 0;
}