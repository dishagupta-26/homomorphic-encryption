#include "math/polynomial.h" // We must include the header file to implement its functions
#include <algorithm>         // Required for std::max

// Implementation of the default constructor
Polynomial::Polynomial() {
    // By default, create a polynomial that is just the constant 0.
    // It has one coefficient, which is 0.
    coefficients.push_back(0);
}

// Implementation of the constructor that takes a degree
Polynomial::Polynomial(size_t degree) {
    // A polynomial of degree 'n' has 'n+1' coefficients.
    // For example, degree 2 (ax^2+bx+c) has 3 coefficients.
    // We initialize them all to zero.
    coefficients.resize(degree + 1, 0);
}

// Implementation of the degree() function
size_t Polynomial::degree() const {
    // The degree is the highest power, which is one less than the number of coefficients.
    // However, we must be careful if the vector is empty or has one element.
    if (coefficients.size() <= 1) {
        return 0;
    }
    return coefficients.size() - 1;
}

// Implementation of the to_string() helper function
std::string Polynomial::to_string() const {
    if (coefficients.empty()) {
        return "0";
    }

    std::string result = "";
    // Loop backwards from the highest-degree coefficient
    for (int i = coefficients.size() - 1; i >= 0; --i) {
        if (coefficients[i] != 0) {
            if (!result.empty()) {
                result += " + ";
            }
            result += std::to_string(coefficients[i]) + "x^" + std::to_string(i);
        }
    }

    if (result.empty()) {
        return "0"; // This happens if all coefficients are zero.
    }
    return result;
}

// --- This is the new function, placed correctly AFTER to_string() is finished ---
Polynomial Polynomial::add(const Polynomial& other) const {
    // Determine the size of the resulting polynomial's coefficient vector.
    // It will be the size of the larger of the two polynomials we're adding.
    size_t result_size = std::max(this->coefficients.size(), other.coefficients.size());
    
    // Create a new polynomial to store the result.
    // We initialize it with the correct degree (size - 1).
    Polynomial result(result_size - 1);

    // Loop through the coefficients of the FIRST polynomial ("this")
    // and add them to our result.
    for (size_t i = 0; i < this->coefficients.size(); ++i) {
        result.coefficients[i] += this->coefficients[i];
    }

    // Loop through the coefficients of the SECOND polynomial ("other")
    // and add them to our result.
    for (size_t i = 0; i < other.coefficients.size(); ++i) {
        result.coefficients[i] += other.coefficients[i];
    }

    // NOTE for the future: In real FHE, every addition is followed by
    // a modulo operation (e.g., result %= modulus). We will add this
    // complexity later when it's needed.

    return result;
}

Polynomial Polynomial::multiply(const Polynomial& other) const {
    // The degree of the result is the sum of the degrees of the input polynomials.
    size_t this_degree = this->degree();
    size_t other_degree = other.degree();
    size_t result_degree = this_degree + other_degree;

    // Create the result polynomial, initialized with all zero coefficients.
    Polynomial result(result_degree);

    // This is the "schoolbook" multiplication algorithm.
    // For each term in the first polynomial ("this")...
    for (size_t i = 0; i < this->coefficients.size(); ++i) {
        // ...multiply it by each term in the second polynomial ("other").
        for (size_t j = 0; j < other.coefficients.size(); ++j) {
            // The new coefficient is the product of the two coefficients.
            // The new term's degree is the sum of the individual degrees (i + j).
            result.coefficients[i + j] += this->coefficients[i] * other.coefficients[j];
        }
    }

    // NOTE for the future: This O(n^2) function is the slow part of FHE.
    // We will later replace it with a much faster O(n*log(n)) version using
    // the Number Theoretic Transform (NTT).

    return result;
}