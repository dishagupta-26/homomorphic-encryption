#ifndef NTT_H
#define NTT_H

#include <vector>
#include <cstdint>
#include <algorithm>
#include "mod_arith.h"

namespace fhe {

class NTT {
public:
    size_t n;
    int64_t q;
    int64_t root;
    int64_t root_inv;
    int64_t n_inv;

    NTT(size_t degree, int64_t modulus)
        : n(degree), q(modulus) {
        root = find_root();
        root_inv = mod_pow(root, q - 2, q);
        n_inv = mod_pow(n, q - 2, q);
    }

    void forward(std::vector<int64_t>& a) {
        bit_reverse(a);

        for (size_t len = 2; len <= n; len <<= 1) {
            int64_t wlen = mod_pow(root, n / len, q);
            for (size_t i = 0; i < n; i += len) {
                int64_t w = 1;
                for (size_t j = 0; j < len / 2; j++) {
                    int64_t u = a[i + j];
                    int64_t v = mod_mul(a[i + j + len / 2], w, q);

                    a[i + j] = mod_add(u, v, q);
                    a[i + j + len / 2] = mod_sub(u, v, q);

                    w = mod_mul(w, wlen, q);
                }
            }
        }
    }

    void inverse(std::vector<int64_t>& a) {
        bit_reverse(a);

        for (size_t len = 2; len <= n; len <<= 1) {
            int64_t wlen = mod_pow(root_inv, n / len, q);
            for (size_t i = 0; i < n; i += len) {
                int64_t w = 1;
                for (size_t j = 0; j < len / 2; j++) {
                    int64_t u = a[i + j];
                    int64_t v = a[i + j + len / 2];

                    a[i + j] = mod_add(u, mod_mul(v, w, q), q);
                    a[i + j + len / 2] =
                        mod_sub(u, mod_mul(v, w, q), q);

                    w = mod_mul(w, wlen, q);
                }
            }
        }

        for (auto& x : a)
            x = mod_mul(x, n_inv, q);
    }

private:
    void bit_reverse(std::vector<int64_t>& a) {
        size_t j = 0;
        for (size_t i = 1; i < n; i++) {
            size_t bit = n >> 1;
            while (j & bit) {
                j ^= bit;
                bit >>= 1;
            }
            j |= bit;
            if (i < j)
                std::swap(a[i], a[j]);
        }
    }

    int64_t find_root() {
        for (int64_t g = 2; g < q; g++) {
            if (mod_pow(g, (q - 1) / (2 * n), q) != 1)
                return mod_pow(g, (q - 1) / (2 * n), q);
        }
        return -1;
    }
};

} // namespace fhe

#endif
