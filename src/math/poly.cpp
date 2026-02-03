#include "poly.h"
#include "mod_arith.h"
#include <stdexcept>

namespace fhe {

Polynomial::Polynomial() : modulus(0) {}

Polynomial::Polynomial(size_t degree, int64_t mod)
    : coeffs(degree, 0), modulus(mod) {}

size_t Polynomial::degree() const {
    return coeffs.size();
}

Polynomial Polynomial::add(const Polynomial& other) const {
    if (degree() != other.degree() || modulus != other.modulus)
        throw std::runtime_error("Polynomial add: incompatible parameters");

    Polynomial result(degree(), modulus);
    for (size_t i = 0; i < degree(); i++) {
        result.coeffs[i] = mod_add(coeffs[i], other.coeffs[i], modulus);
    }
    return result;
}

Polynomial Polynomial::sub(const Polynomial& other) const {
    if (degree() != other.degree() || modulus != other.modulus)
        throw std::runtime_error("Polynomial sub: incompatible parameters");

    Polynomial result(degree(), modulus);
    for (size_t i = 0; i < degree(); i++) {
        result.coeffs[i] = mod_sub(coeffs[i], other.coeffs[i], modulus);
    }
    return result;
}

Polynomial Polynomial::mul_naive(const Polynomial& other) const {
    if (degree() != other.degree() || modulus != other.modulus)
        throw std::runtime_error("Polynomial mul: incompatible parameters");

    size_t n = degree();
    Polynomial result(n, modulus);

    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n; j++) {
            size_t idx = (i + j) % n;
            int64_t sign = ((i + j) >= n) ? -1 : 1; // x^n = -1
            int64_t value = mod_mul(coeffs[i], other.coeffs[j], modulus);
            result.coeffs[idx] =
                mod_add(result.coeffs[idx], sign * value, modulus);
        }
    }
    return result;
}

void Polynomial::reduce() {
    for (auto& c : coeffs)
        c = mod(c, modulus);
}

} // namespace fhe
