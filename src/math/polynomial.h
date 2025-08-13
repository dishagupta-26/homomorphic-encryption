#pragma once // A standard way to prevent this file from being included multiple times

#include <vector>   // We need this to use std::vector for our coefficients
#include <cstdint>  // We need this for fixed-size integers like uint64_t
#include <string>   // We need this for a helper function to print the polynomial
#include "scheme/params.h"


class Polynomial {
public:
    // --- Member Variables ---

    // This vector will hold the coefficients of our polynomial.
    // For a polynomial a*x^2 + b*x + c, the vector would be {c, b, a}.
    std::vector<uint64_t> coefficients;

    // --- Constructors ---

    // A "default" constructor to create a simple, zero polynomial.
    Polynomial();

    // A constructor to create a polynomial of a specific degree.
    Polynomial(size_t degree);

    // --- Member Functions ---

    // A function to get the degree of the polynomial.
    // The "const" means this function doesn't modify the polynomial.
    size_t degree() const;

    // A helper function to represent the polynomial as a human-readable string for debugging.
    std::string to_string() const;

    // Adds another polynomial to this one and returns the result.
    Polynomial add(const Polynomial& other) const;

    // Modify the declaration of the multiply function to accept Parameters
    Polynomial multiply(const Polynomial& other, const Parameters& params) const;
};