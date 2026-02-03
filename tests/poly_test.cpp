#include <iostream>
#include "math/poly.h"

int main() {
    fhe::Polynomial a(4, 17);
    fhe::Polynomial b(4, 17);

    a.coeffs = {1, 2, 3, 4};
    b.coeffs = {4, 3, 2, 1};

    auto c = a.add(b);
    auto d = a.mul_naive(b);

    std::cout << "Add: ";
    for (auto x : c.coeffs) std::cout << x << " ";
    std::cout << "\nMul: ";
    for (auto x : d.coeffs) std::cout << x << " ";
    std::cout << std::endl;
}
