#ifndef RANDOM_H
#define RANDOM_H

#include <random>
#include <cstdint>

namespace fhe {

inline int64_t uniform_int(int64_t min, int64_t max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int64_t> dist(min, max);
    return dist(gen);
}

inline int64_t small_noise(int64_t bound) {
    return uniform_int(-bound, bound);
}

} // namespace fhe

#endif
