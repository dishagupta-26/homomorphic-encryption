#include <iostream>
#include "lattice/rlwe_encrypt.h"
#include "lattice/rlwe_params.h"


int main() {
    fhe::RLWEParams params(8, 17, 2, 1);

    auto sk = fhe::RLWEKeyGen::generate_secret(params);
    auto pk = fhe::RLWEKeyGen::generate_public(params, sk);

    fhe::Polynomial m(params.n, params.q);
    m.coeffs[0] = 5; // encrypt message "5"

    auto ct = fhe::RLWEEncrypt::encrypt(params, pk, m);

    std::cout << "c0: ";
    for (auto x : ct.c0.coeffs) std::cout << x << " ";
    std::cout << "\nc1: ";
    for (auto x : ct.c1.coeffs) std::cout << x << " ";
    std::cout << std::endl;
}
