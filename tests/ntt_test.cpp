#include <iostream>
#include "math/ntt.h"

int main() {
    const size_t n = 8;
    const int64_t q = 17;

    fhe::NTT ntt(n, q);

    std::vector<int64_t> a = {1,2,3,4,0,0,0,0};
    std::vector<int64_t> b = {4,3,2,1,0,0,0,0};

    auto fa = a;
    auto fb = b;

    ntt.forward(fa);
    ntt.forward(fb);

    for (size_t i = 0; i < n; i++)
        fa[i] = fhe::mod_mul(fa[i], fb[i], q);

    ntt.inverse(fa);

    std::cout << "Result: ";
    for (auto x : fa) std::cout << x << " ";
    std::cout << std::endl;
}
