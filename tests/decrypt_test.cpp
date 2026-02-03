#include <iostream>
#include "lattice/rlwe_encrypt.h"
#include "lattice/rlwe_decrypt.h"
#include "lattice/rlwe_params.h"


int main() {
    fhe::RLWEParams params(8, 17, 2, 1);

    auto sk = fhe::RLWEKeyGen::generate_secret(params);
    auto pk = fhe::RLWEKeyGen::generate_public(params, sk);

    fhe::Polynomial m(params.n, params.q);
    m.coeffs[0] = 5;

    auto ct = fhe::RLWEEncrypt::encrypt(params, pk, m);
    auto decrypted = fhe::RLWEDecrypt::decrypt(sk, ct, params);

    std::cout << "Decrypted: ";
    for (auto x : decrypted.coeffs)
        std::cout << x << " ";
    std::cout << std::endl;
}
