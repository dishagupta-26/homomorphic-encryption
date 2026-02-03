#include <iostream>
#include "lattice/rlwe_params.h"

int main() {
    fhe::RLWEParams params(8, 17, 1);
    std::cout << "n=" << params.n
              << " q=" << params.q
              << " noise=" << params.noise << std::endl;
}
