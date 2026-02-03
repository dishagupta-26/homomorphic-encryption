#include <iostream>
#include "lattice/rlwe_keygen.h"

int main() {
    fhe::RLWEParams params(8, 17, 2, 1);

    auto sk = fhe::RLWEKeyGen::generate_secret(params);
    auto pk = fhe::RLWEKeyGen::generate_public(params, sk);

    std::cout << "Secret key s: ";
    for (auto x : sk.s.coeffs) std::cout << x << " ";
    std::cout << "\nPublic key a: ";
    for (auto x : pk.a.coeffs) std::cout << x << " ";
    std::cout << "\nPublic key b: ";
    for (auto x : pk.b.coeffs) std::cout << x << " ";
    std::cout << std::endl;
}
