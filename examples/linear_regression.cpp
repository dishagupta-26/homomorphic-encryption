#include <iostream>
#include "math/polynomial.h"

int main() {
    std::cout << "--- FHE Framework Test ---" << std::endl;

    // Create two simple polynomials for our tests
    // p1 = 2x + 3
    Polynomial p1(1);
    p1.coefficients = {3, 2};
    std::cout << "p1 = " << p1.to_string() << std::endl;

    // p2 = 4x + 5
    Polynomial p2(1);
    p2.coefficients = {5, 4};
    std::cout << "p2 = " << p2.to_string() << std::endl;
    std::cout << "--------------------------------" << std::endl;


    // --- Test 1: Addition ---
    std::cout << "\nTesting Addition..." << std::endl;
    Polynomial sum = p1.add(p2); // (2x+3) + (4x+5) = 6x + 8
    std::cout << "p1 + p2 = " << sum.to_string() << std::endl;
    std::cout << "Expected:  6x^1 + 8x^0" << std::endl;


    // --- Test 2: Multiplication ---
    std::cout << "\nTesting Multiplication..." << std::endl;
    Polynomial product = p1.multiply(p2); // (2x+3)*(4x+5) = 8x^2 + 22x + 15
    std::cout << "p1 * p2 = " << product.to_string() << std::endl;
    std::cout << "Expected:  8x^2 + 22x^1 + 15x^0" << std::endl;


    std::cout << "\n--- Test Complete ---" << std::endl;
    return 0;
}