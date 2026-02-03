#ifndef POLY_H
#define POLY_H

#include <vector>
#include <cstdint>
#include <cstddef>   // for size_t

namespace fhe {

class Polynomial {
public:
    std::vector<int64_t> coeffs;
    int64_t modulus;

    Polynomial();
    Polynomial(size_t degree, int64_t mod);

    size_t degree() const;

    Polynomial add(const Polynomial& other) const;
    Polynomial sub(const Polynomial& other) const;
    Polynomial mul_naive(const Polynomial& other) const;

    void reduce();
};

} // namespace fhe

#endif
